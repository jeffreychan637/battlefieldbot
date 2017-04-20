from multiprocessing import Queue
from threading import Thread
import time

import audio_processor as Audio

from socketIO_client import SocketIO, BaseNamespace

COMMANDS = ["fire", "retrieve", "stop"]

def keyboard_processor(commands):
    while True:
        command = raw_input("Enter Command: ")
        if command == "f":
            commands.put("fire")
        elif command == "r":
            commands.put("retrieve")
        elif command == "s":
            commands.put("stop")

def main():
    socketIO = SocketIO('localhost', 5000)
    audio_socket = socketIO.define(Audio.AudioNamespace, '/audio')
    audio_socket.on('connect', audio_socket.on_connect)
    audio_socket.on('disconnect', audio_socket.on_disconnect)

    commands = Queue()

    command_executor = Thread(target=Audio.execute_commands, args=(commands, audio_socket))
    command_executor.daemon = True
    command_executor.start()

    keyboard_processor(commands)

if __name__ == '__main__': main()
