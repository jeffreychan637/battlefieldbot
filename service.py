import socket
import sys
import select

import keras
import csv
import numpy as np
from keras.preprocessing import sequence

from oracle_forward_stepping import *

import queue
import threading

import time
from keras.models import model_from_json

mappingsfname = 'tp_mappings.csv'
mappings = {}
with open(mappingsfname, 'rt') as csvfile:
    mappingsreader = csv.reader(csvfile)
    for row in mappingsreader:
        mappings[int(row[0])] = row[1]
vocab_size = len(mappings)
vocab_size = 194

indices_to_drop = [400, 401, 402, 403, 404, 405, 406, 407]

def find_best(model, seq):
    # Returns either -1 or (index, time bucket, # forward steps used)
    # Filters input sequence on blacklisted events and repeats
    result = forward_step_to_meaningful_bucket(model, seq, vocab_size)
    if result == -1:
        return result
    else:
        return str(result[0])

class Server:
    sock_to_req = dict()
    queue = queue.Queue()
    socket_list = []

    def __init__(self):
        self.socket = socket.socket()
        self.socket.bind(("127.0.0.1", 1343))
        self.socket.listen(30)
        Server.socket_list.append(self.socket)
        self.rec()

    def rec(self):

        num_worker_threads = 1
        for i in range(num_worker_threads):
             t = threading.Thread(target=self.worker)
             t.daemon = True
             t.start()

        while True:
            ready_to_read , ready_to_write, in_error = select.select(Server.socket_list,[],[])
            for sock in ready_to_read:
                # a new connection request recieved
                if sock == self.socket:
                    sockfd, addr = self.socket.accept()
                    Server.socket_list.append(sockfd)

                # a request from a client, not a new connection
                else:
                    data = sock.recv(20000)
                    if data:
                        Server.sock_to_req[sock] = data
                        Server.queue.put(sock)

                    else:
                        if sock in Server.socket_list:
                            Server.socket_list.remove(sock)

                        if sock in Server.sock_to_req:
                            del Server.sock_to_req[sock]

                        sock.close()

        self.socket.close()

    def worker(self):
        with open("tp_arch.json", "r") as a:
            tp_json = a.read()

        keras_model = model_from_json(tp_json)
        keras_model.load_weights('tp_weights.h5')
        while True:
            start = time.time()

            # process request
            s = Server.queue.get()
            req = Server.sock_to_req[s].decode("utf-8")
            nums = req.split(" ")
            offset = len(nums) // 2
            seq = []
            i = 0
            print(req)
            while i < offset:
                index = int(nums[i])
                if index not in indices_to_drop:
                    seq.append([index, int(nums[i+offset])])
                i += 1
            print(seq)
            res = str(find_best(keras_model, seq))

            print("Time for model: " + str((time.time() - start)*1000.0))

            # send response from model
            s.send(res.encode())
            Server.queue.task_done()

s = Server()
