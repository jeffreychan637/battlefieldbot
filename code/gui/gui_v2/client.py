from socketIO_client import SocketIO, BaseNamespace
import time

class clientNamespace(BaseNamespace):

    def on_connect(self):
        print('client connected')

    def on_disconnect(self):
        print('client disconnected')

socketIO = SocketIO('localhost', 5000)


client = socketIO.define(clientNamespace, '/client')
client.on('connect', client.on_connect)
client.on('disconnect', client.on_disconnect)

client.emit('sonar_dist', {'data': '40'})
client.emit('sonar_dist', {'data': '35'})
client.emit('sonar_dist', {'data': '15'})
client.emit('sonar_dist', {'data': '5'})

client.emit('state', {'data': 'avoidance'})

client.emit('dest', {'data': '(20,30)'})
client.emit('curr', {'data': '(0,0)'})
client.emit('curr', {'data': '(-2,10)'})
client.emit('curr', {'data': '(5,15)'})
client.emit('curr', {'data': '(10,20)'})
client.emit('curr', {'data': '(25,25)'})
client.emit('curr', {'data': '(20,30)'})

client.emit('accel_X', {'data': '3'})
client.emit('accel_Y', {'data': '5'})

time.sleep(3)

client.emit('sonar_dist', {'data': '40'})
client.emit('sonar_dist', {'data': '35'})
client.emit('sonar_dist', {'data': '15'})
client.emit('sonar_dist', {'data': '5'})

client.emit('state', {'data': 'goal'})
