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
    audio_socket = Audio.setup_socket()
    commands = Queue()

    command_executor = Thread(target=Audio.execute_commands, args=(commands, audio_socket))
    command_executor.daemon = True
    command_executor.start()

    keyboard_processor(commands)

if __name__ == '__main__': main()
