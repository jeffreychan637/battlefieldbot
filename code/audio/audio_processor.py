import speech_recognition as sr
from multiprocessing.pool import ThreadPool

COMMANDS = ["fire", "retrieve", "stop"]
GOOGLE_CLOUD_SPEECH_CREDENTIALS = "Google_Speech_API_Secret"
POOL_SIZE = 10

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

def process_audio(audio, recognizer):
    result = get_text_from_Google(audio, recognizer)
    if result and result.strip() in COMMANDS:
        print("Command Sent: " + result)
        #send result.strip() to PSOC
        #send result.strip() to GUI
    return

def main():
    pool = ThreadPool(processes=POOL_SIZE)
    recognizer = sr.Recognizer()

    with sr.Microphone() as source:
        while True:
            recognizer.adjust_for_ambient_noise(source)
            # Note that audio will be sent out every 5 seconds regardless of speech
            # This is done to prevent multiple commands from being lumped together
            audio = recognizer.listen(source, phrase_time_limit=5)
            # Use a worker thread to process the audio while continuing to listen
            pool.apply_async(process_audio, (audio, recognizer))

if __name__ == '__main__': main()
