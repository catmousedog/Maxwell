import cv2 as cv
import numpy as np
import yaml
import time
import os


import relatpy

# autocomplete not working?
p = relatpy.Position(1, 2, 1)
assert(p.x == 2.0)

__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))

with open(os.path.join(__location__, 'settings.yaml'), "r") as stream:
    settings = yaml.safe_load(stream)

    width = settings['width']
    height = settings['height']
    FPS = settings['FPS']

R = np.array([0.5, 0.6])
A = 0.2

C = 0.5
b = 0.8

N = 4

dt = 1 / FPS

# test function for now


def square(x, y, a):
    poly = np.array([[0, 0], [1, 0], [1, 1], [0, 1]])

    poly[:, 0] *= int(width * a)
    poly[:, 1] *= int(height * a)

    poly[:, 0] += int(x * width)
    poly[:, 1] += int(y * height)

    return poly


def draw():
    blank = np.zeros((width, height), dtype='uint8')
    cv.polylines(blank, [polygon], True, (255, 255, 255))
    cv.imshow('Relativity', blank)


def tick(dt):

    draw()

    return cv.waitKey(1)


polygon = square(R[0], R[1], A)

clock_now = time.process_time()
clock_prev = clock_now - dt - 1

while True:

    if clock_now - clock_prev >= dt:
        key = tick(clock_now - clock_prev)
        clock_prev = clock_now

        # Esc key to stop
        if key == 27:
            cv.destroyAllWindows()
            break

    clock_now = time.process_time()
