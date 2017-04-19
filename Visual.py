import json

class Visual:
    def __init__(self):
        self.visual_distance_to_target = 5
        self.visual_angle_to_target = 30
        self.visual_size_of_target = 0.80
        self.visual_center_of_target = (0.50, 0.50)
        self.visual_time_to_new_image = 30
        self.visual_time_to_execute = 40
        self.images = "images/"

    def toJson(self):
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)

# print(Visual().toJson())
