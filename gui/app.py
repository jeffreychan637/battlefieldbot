from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit

app = Flask(__name__)
socketio = SocketIO(app, async_mode='gevent')

@app.route("/")
def chart():
    labels = ["January","February","March","April","May","June","July","August"]
    values = [10,9,8,7,6,4,7,8]
    return render_template('chart.html', values=values, labels=labels, async_mode=socketio.async_mode)

@socketio.on('connect', namespace='/gui')
def gui_connect():
    print 'connected gui'

################################################################

@socketio.on('connect', namespace='/audio')
def audio_connect():
    print 'connected audio'

@socketio.on('audio_command', namespace='/audio')
def audio_command(msg):
    print 'audio command received by server'
    send_audio_command(msg)

def send_audio_command(msg):
    print msg
    socketio.emit('audio_command', msg, namespace='/gui')

@socketio.on('audio_executed', namespace='/audio')
def audio_executed():
    print 'audio execution done'
    send_audio_executed()

def send_audio_executed():
    socketio.emit('audio_executed', namespace='/gui')

################################################################

@socketio.on('visual_image_received', namespace='/visual')
def visual_image_received():
    print 'visual image received'
    send_visual_image_received()

def send_visual_image_received():
    socketio.emit('visual_image_received', namespace='/gui')

@socketio.on('visual_info', namespace='/visual')
def visual_info(msg):
    print 'visual info received'
    print msg
    send_visual_info(msg)

def send_visual_info(msg):
    socketio.emit('visual_info', msg, namespace='/gui')

@socketio.on('visual_executed', namespace='/visual')
def visual_executed():
    print 'visual execution done'
    send_visual_executed()

def send_visual_executed():
    socketio.emit('visual_executed', namespace='/gui')

if __name__ == "__main__":
    print 'Starting Server'
    socketio.run(app, host='127.0.0.1', port=5000)
