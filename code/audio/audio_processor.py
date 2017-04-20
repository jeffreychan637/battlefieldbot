from multiprocessing import Queue
from multiprocessing.pool import ThreadPool
from threading import Thread
import time

import speech_recognition as sr
from socketIO_client import SocketIO, BaseNamespace


COMMANDS = ["fire", "retrieve", "stop"]
GOOGLE_CLOUD_SPEECH_CREDENTIALS = "Google_Speech_API_Secret"
POOL_SIZE = 10

class AudioNamespace(BaseNamespace):

    def on_connect(self):
        print('audio connected')

    def on_disconnect(self):
        print('audio disconnected')

def get_text_from_Google(audio, recognizer):
    try:
        print("Contacting Google")
        result = recognizer.recognize_google_cloud(audio, credentials_file=GOOGLE_CLOUD_SPEECH_CREDENTIALS)
        print("Recognized Audio: " + result)
        return result
    except sr.UnknownValueError:
        print("Google Cloud Speech could not understand audio")
    except sr.RequestError as e:
        print("Could not request results from Google Cloud Speech service; {0}".format(e))

def process_audio(audio, recognizer, commands):
    result = get_text_from_Google(audio, recognizer)
    if result and result.strip() in COMMANDS:
        commands.put(result.strip())
    return

def execute_commands(commands, audio_socket):
    while True:
        command = commands.get(True) # blocks until command received
        audio_socket.emit('audio_command', {'data': command})
        print("Command Sent: " + command)

        # send command to PSOC
        # block until PSOC confirms command has been executed
        time.sleep(8)

        audio_socket.emit('audio_executed')
        print("Executed notification sent")

def main():
    pool = ThreadPool(processes=POOL_SIZE)
    recognizer = sr.Recognizer()

    socketIO = SocketIO('localhost', 5000)
    audio_socket = socketIO.define(AudioNamespace, '/audio')
    audio_socket.on('connect', audio_socket.on_connect)
    audio_socket.on('disconnect', audio_socket.on_disconnect)

    commands = Queue()

    command_executor = Thread(target=execute_commands, args=(commands, audio_socket))
    command_executor.daemon = True
    command_executor.start()

    with sr.Microphone() as source:
        while True:
            recognizer.adjust_for_ambient_noise(source)
            # Note that audio will be sent out every 5 seconds regardless of speech
            # This is done to prevent multiple commands from being lumped together
            audio = recognizer.listen(source, phrase_time_limit=5)
            # Use a worker thread to process the audio while continuing to listen
            pool.apply_async(process_audio, (audio, recognizer, commands))

if __name__ == '__main__': main()
