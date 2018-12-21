import numpy as np
import cv2
import urllib2 as ul
import json
from time import sleep


left='https://api.thingspeak.com/update?api_key=2RTLL7AXEYOAVUX1&field1='
right='https://api.thingspeak.com/update?api_key=2RTLL7AXEYOAVUX1&field2='
front='https://api.thingspeak.com/update?api_key=2RTLL7AXEYOAVUX1&field3='
back='https://api.thingspeak.com/update?api_key=2RTLL7AXEYOAVUX1&field4='
stop='https://api.thingspeak.com/update?api_key=2RTLL7AXEYOAVUX1&field5='


cap=cv2.VideoCapture(0)

while True:
  ret, frame=cap.read()
  gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
  #cv2.imshow('frame',frame)
  circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT,1,400)
  if circles is not None:
        circles = np.uint16(np.around(circles))
        for i in circles[0, :]:
            center = (i[0], i[1])
            # circle center
            cv2.circle(frame, center, 1, (100, 100, 100), 1)
            # circle outline
            radius = i[2]
            cv2.circle(frame, center, radius, (255, 0, 255), 3)
            ## [draw]
            print("center =")
            print(center)
            print("radius")
            print(radius)
            x=i[0]
            y=i[1]
            z=i[2]

            if    400 < x < 600 :
             print("LEFT")
             ul.urlopen(left + str(20))
             ul.urlopen(right + str(0))
              

            if    200 < x <300 :
             print("RIGHT")
             ul.urlopen(left + str(0))
             ul.urlopen(right + str(120))

            if  90<z<(105):
             print("FRONT")
             ul.urlopen(front + str(1))
             ul.urlopen(stop + str(0))
             ul.urlopen(back + str(0))
             
            elif  106<z<120:
             print("stop")
             ul.urlopen(front + str(0))
             ul.urlopen(stop + str(1))
             ul.urlopen(back + str(0))

            elif  121<z<140:
             print("BACK")
             ul.urlopen(stop + str(0))
             ul.urlopen(back + str(1))
             ul.urlopen(front + str(0))

          
            ## [display]
  cv2.imshow('detected circles',frame)
  if cv2.waitKey(1) & 0xFF == ord('q'):
        break
        break
cap.release()
cv2.destroyAllWindows()
