from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit

app = Flask(__name__)
socketio = SocketIO(app, async_mode='gevent')

@app.route("/")
def chart():
    return render_template('index.html', async_mode=socketio.async_mode)

@socketio.on('connect', namespace='/gui')
def gui_connect():
    print 'connected gui'

################################################################

@socketio.on('connect', namespace='/client')
def client_connect():
    print 'connected client'

################################################################

@socketio.on('sonar_dist', namespace='/client')
def sonar_dist(msg):
    print 'sonar command received by server'
    send_sonar_dist(msg)

def send_sonar_dist(msg):
    print msg
    socketio.emit('sonar_dist', msg, namespace='/gui')

################################################################

@socketio.on('state', namespace='/client')
def state(msg):
    print 'state'
    send_state(msg)

def send_state(msg):
    print msg
    socketio.emit('state', msg, namespace='/gui')

################################################################

@socketio.on('curr', namespace='/client')
def curr(msg):
    print 'curr'
    send_curr(msg)

def send_curr(msg):
    print msg
    socketio.emit('curr', msg, namespace='/gui')

################################################################

@socketio.on('dest', namespace='/client')
def dest(msg):
    print 'dest'
    send_dest(msg)

def send_dest(msg):
    print msg
    socketio.emit('dest', msg, namespace='/gui')

################################################################

@socketio.on('accel_X', namespace='/client')
def accel_X(msg):
    print 'accel_X'
    send_accel_X(msg)

def send_accel_X(msg):
    print msg
    socketio.emit('accel_X', msg, namespace='/gui')

################################################################

@socketio.on('accel_Y', namespace='/client')
def accel_Y(msg):
    print 'accel_Y'
    send_accel_Y(msg)

def send_accel_Y(msg):
    print msg
    socketio.emit('accel_Y', msg, namespace='/gui')

################################################################

if __name__ == "__main__":
    print 'Starting Server'
    socketio.run(app, host='127.0.0.1', port=5000)
