import pygame
import sys
from pygame.locals import *
from relatpy import vec3, vel2, vec2, RigidBody, Integrator, Frame
from math import *

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
FRAME_SIZE = 10
FPS = 60
TPS = 1  # Time per second

pygame.init()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Interactive Point Drawing")


def convert_to_pixels(coord):
    x_pixel = int((coord.x + FRAME_SIZE) / (2 * FRAME_SIZE) * SCREEN_WIDTH)
    y_pixel = int((-coord.y + FRAME_SIZE) / (2 * FRAME_SIZE) * SCREEN_HEIGHT)
    return x_pixel, y_pixel


initial_pos = vec2(-9, 9)
initial_vel = vel2(0, 0.)
initial_accel = vec2(.9, 0)

frame = Frame()
rigidbody = RigidBody(frame, initial_pos, initial_vel, initial_accel)
l = 5
N = 10
points = []
for i in range(N):
    points.append(rigidbody.addPoint(vec2(l*i/N, 0)))


clock = pygame.time.Clock()

integrator = Integrator(frame)
integrator.addBody(rigidbody)
integrator.setup()
bodies = integrator.getBodies()

pressed_keys = set()
i = 0
prev_accel = initial_accel
bool1 = True
bool2 = True
bool3 = True
bool4 = True

# for some reason this fixes error???
ttt = integrator.getBodies()[0].getPoints()

def Approx(num1, num2, tolerance=1e-2):
    return abs(num1 - num2) < tolerance

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == K_w and pygame.key.get_mods() & KMOD_CTRL:
                pygame.quit()
                sys.exit()
            else:
                pressed_keys.add(event.key)
        elif event.type == pygame.KEYUP:
            pressed_keys.discard(event.key)

    accel = vec2(0, 0)
    accel.x = .4 * ((K_RIGHT in pressed_keys) - (K_LEFT in pressed_keys))
    accel.y = .4 * ((K_UP in pressed_keys) - (K_DOWN in pressed_keys))
    if accel.x != prev_accel.x or accel.y != prev_accel.y:
        if rigidbody.updateAccel(accel):
            prev_accel = accel
            print(f"YES: {accel.x}, {accel.y}")
        else:
            print(f"NO: {accel.x}, {accel.y}")

    for _ in range(10):
        integrator.step(TPS / FPS / 10.)

    screen.fill(BLACK)

    points = []
    for body in integrator.getBodies():
        points.extend(body.getPoints())

    pixel_positions = [convert_to_pixels(point.pos) for point in points]
    for pixels in pixel_positions:
        pygame.draw.circle(screen, WHITE, pixels, 2)
    pygame.draw.lines(screen, WHITE, False, pixel_positions, 1)

    pygame.display.flip()

    clock.tick(FPS)
    i += 1
