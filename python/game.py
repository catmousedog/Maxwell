import pygame
import sys
from pygame.locals import K_w, KMOD_CTRL
from relatpy import vec3, vel2, vec2, Body, Integrator, Frame

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


initial_pos = vec3(0, -5, -5)
initial_vel = vel2(0, 0)
initial_accel = vec2(1.5, 1.5)

body = Body(initial_pos, initial_vel, initial_accel)
l = 4
body.addPoint(vec2(l, 0))
body.addPoint(vec2(l, l))
body.addPoint(vec2(0, l))

points = body.getPoints()


clock = pygame.time.Clock()

integrator = Integrator(Frame())
integrator.addPoint(body)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == K_w and pygame.key.get_mods() & KMOD_CTRL:
                pygame.quit()
                sys.exit()

    integrator.step(TPS / FPS)

    screen.fill(BLACK)

    pixel_positions = [convert_to_pixels(point.pos) for point in points]
    for pixels in pixel_positions:
        pygame.draw.circle(screen, WHITE, pixels, 4)
    pygame.draw.polygon(screen, WHITE, pixel_positions, 1)

    pygame.display.flip()

    clock.tick(FPS)
