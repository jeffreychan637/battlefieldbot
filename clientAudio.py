from socketIO_client import SocketIO, BaseNamespace
import time

class AudioNamespace(BaseNamespace):

    def on_connect(self):
        print('audio connected')

    def on_disconnect(self):
        print('audio disconnected')

socketIO = SocketIO('localhost', 5000)
a_name = socketIO.define(AudioNamespace, '/audio')
a_name.on('connect', a_name.on_connect)
a_name.on('disconnect', a_name.on_disconnect)

a_name.emit('audio_command', {'data': 'Fire'})
time.sleep(5)
a_name.emit('audio_executed')
