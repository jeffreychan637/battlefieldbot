import json

class Audio:

    def __init__(self):
        self.audio_command = ["Retrieve"]
        self.audio_time_to_execute = 20

    def toJson(self):
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)

print(Audio().toJson())
