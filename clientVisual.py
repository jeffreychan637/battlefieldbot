from socketIO_client import SocketIO, BaseNamespace
import time

class VisualNamespace(BaseNamespace):

    def on_connect(self):
        print('visual connected')

    def on_disconnect(self):
        print('visual disconnected')

socketIO = SocketIO('localhost', 5000)
v_name = socketIO.define(VisualNamespace, '/visual')
v_name.on('connect', v_name.on_connect)
v_name.on('disconnect', v_name.on_disconnect)

v_name.emit('visual_image_received')
v_name.emit('visual_info', {'angle': '55', 'size_target': '80', 'center': '(32, 68)'})

time.sleep(5)

v_name.emit('visual_executed')
v_name.emit('visual_image_received')
