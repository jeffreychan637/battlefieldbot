import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')
import numpy as np
import cv2

object_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
inner_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')

print(object_cascade)
print(inner_cascade)

img = cv2.imread('face_gradient.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

objects = object_cascade.detectMultiScale(gray, 1.3, 5)
print(objects)

for (x,y,w,h) in objects:
    cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2) # Originally had "img ="
    roi_gray = gray[y:y+h, x:x+w]
    roi_color = img[y:y+h, x:x+w]
    inners = inner_cascade.detectMultiScale(roi_gray)
    for (ex,ey,ew,eh) in inners:
        cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)

object_centers = [(x + (w / 2), y + (h / 2)) for (x, y , w, h) in objects]
for (x, y) in object_centers:
	cv2.circle(img, (x, y), 1, (0,0,255), -1)
print(object_centers)

cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()