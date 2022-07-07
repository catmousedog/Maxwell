import cv2 as cv
import numpy as np
import yaml

with open("settings.yaml", "r") as stream:
    settings = yaml.safe_load(stream)

    width = settings['width']
    height = settings['height']


blank = np.zeros((width, height), dtype='uint8')
N = 5
polygon = np.random.randint(0, width, (N, 2))

while(1):
    
    cv.imshow('Relativity', blank)
    
    cv.polylines(blank, [polygon], True, (255,255,255))
    k = cv.waitKey(33)
    # Esc key to stop
    if k == 27:
        break
    # normally -1 returned,so don't print it
    elif k == -1:
        continue
    # else print its value
    else:
        blank = np.zeros((width, height), dtype='uint8')
        polygon = np.random.randint(0, width, (N, 2))
        print(k)
