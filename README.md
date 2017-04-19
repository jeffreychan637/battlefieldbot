# battlebot
This is a project to create a car that can take in voice commands to detect a target, fire at it, or retreive the target.

The car will be controlled via a PSOC 4 microcontroller. For the scope of this project, the car will not actually fire or retrieve targets but simply receive commands to fire as well as be able to drive up to a target and back.

This project contains a GUI that gives information about what the car is up to (e.g. commands received, what the car sees, angle the car is driving at to get to the target). The project also comes with a simulator that details what the car is doing. Within the simulator, you can see the car actually fire at the target or retrieve it.

An accompanying computer receives voice commands and sends them to the car for real-time execution of commands. Voice commands available are "fire", "retrieve", and "stop". Voice to text conversion is done through the Google Cloud Speech API. This is all done with multi-tasking as the audio processor is always listening for audio and the heard audio is processed via background threads. There is also an included keyboard processor that processes commands sent in via the keyboard ("f", "r", "s") and sends them to the car for real-time execution.

Using a camera that takes images in real-time, a visual processor on an accompanying computer receives these images and analyzes them to detect targets and determine the angle the car needs to be steered to get to the target. Commands to adjust the angle and turn the car are sent to the car to be processed in real-time.

### Audio Processor Setup
1. Download dependencies
```
$ cd battlebot
$ virtualenv env
$ source env/bin/activate
$ brew install portaudio
$ pip install -r requirements.txt
```

2. Setup Google Cloud Account
Follow [Google's Getting Started Guide](https://cloud.google.com/speech/docs/getting-started)
* When getting the credentials Setting role as project owner works fine
* Save credentials as “Google_Speech_API_Secret” in the code/audio folder

3. Replace `battlefieldbot/env/lib/python2.7/site-packages/speech_recognition/__init__.py` with this [updated version](https://github.com/jeffreychan637/speech_recognition/blob/google-json-file/speech_recognition/__init__.py).
* This updated version allows for your secret Google Speech API credentials to be stored as a file instead of manually written within the audio code in a JSON format.
