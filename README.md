# Battlefield Bot
This is a project to create a hardware car that can take in voice commands to detect a target, fire at it, or retrieve the target. This kind of robot would be extremely used in a battlefield environment, thus earning the name, _Battlefield Bot_.

The car will be controlled via a PSOC 4 microcontroller. For the scope of this project, the car will not actually fire or retrieve targets but simply receive commands to fire as well as be able to drive up to a target and back.

This project contains a GUI that gives information about what the car is up to (e.g. commands received, what the car sees, angle the car is driving at to get to the target). The project also comes with a simulator that details what the car is doing. Within the simulator, you can see the car actually fire at the target or retrieve it.

An accompanying computer receives voice commands and sends them to the car for real-time execution of commands. Voice commands available are _fire_, _retrieve_, and _stop_. Voice to text conversion is done through the Google Cloud Speech API. This is all done with multi-tasking as the audio processor is always listening for audio and the heard audio is processed via background threads. There is also an included keyboard processor that processes commands sent in via the keyboard (_f_, _r_, _s_) and sends them to the car for real-time execution.

Using a camera that takes images in real-time, a visual processor on an accompanying computer receives these images and analyzes them to detect targets and determine the angle the car needs to be steered to get to the target. Commands to adjust the angle and turn the car are sent to the car to be processed in real-time.

## Running the Battlefield Bot
1. Follow the setup instructions for the individual processors.

2. Start the processors, GUI, and simulators
```
$ cd battlebot
$ virtualenv env
$ source env/bin/activate
```

In separate tabs (one for each line):
```
$ cd code/audio; python audio_processor.py
$ cd code/audio; python keyboard_processor.py // This is optional
$ cd code/visual; python canny_edge_detector.py
$ cd code/visual; python object_detector.py
$ cd code/gui; python app.py
$ cd code/simulation; python simulation.py
```

### Audio Processor Setup
_Note that the keyboard processor is an alternative to the audio processor. It takes in commands via the keyboard instead of the microphone and does not require setup of a Google Cloud Account._

1. Download dependencies
    1. This will download all dependencies including ones for the Visual Processor, GUI, and simulators.
```
$ cd battlebot
$ virtualenv env
$ source env/bin/activate
$ brew install portaudio
$ pip install -r requirements.txt
```

If you have issues with installing the PyAudio dependencies, running this command found [here](http://stackoverflow.com/questions/33513522/when-installing-pyaudio-pip-cannot-find-portaudio-h-in-usr-local-include) might help.
```
$ pip install --global-option='build_ext' --global-option='-I/usr/local/include' --global-option='-L/usr/local/lib' pyaudio
```

2. Setup Google Cloud Account
* Follow [Google's Getting Started Guide](https://cloud.google.com/speech/docs/getting-started)
* When getting the credentials Setting role as project owner works fine
* Save credentials as “Google_Speech_API_Secret” in the code/audio folder

3. Replace `battlefieldbot/env/lib/python2.7/site-packages/speech_recognition/__init__.py` with this [updated version](https://github.com/jeffreychan637/speech_recognition/blob/google-json-file/speech_recognition/__init__.py).
* This updated version allows for your secret Google Speech API credentials to be stored as a file instead of manually written within the audio code in a JSON format.

## Setup
### Visual Processor Setup
1. Download dependencies
    1. This will download all dependencies including ones for the Audio Processor, GUI, and simulators.
```
$ cd battlebot
$ virtualenv env
$ source env/bin/activate
$ brew install portaudio
$ pip install -r requirements.txt
```

2. Test the Canny Edge Detector
```
$ cd code/visual
$ python canny_edge_detector.py
```
If you run into issues with `matplotlib` where Python needs to be installed as a framework, a possible solution can be found [here](http://stackoverflow.com/questions/29433824/unable-to-import-matplotlib-pyplot-as-plt-in-virtualenv).

3. Test the Object Detector
```
$ cd code/visual
$ python object_detector.py
```
If you run into issues with OpenCV needed to be reconfigured, a possible solution can be found [here]().
