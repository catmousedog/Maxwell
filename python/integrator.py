import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.widgets import Slider
import numpy as np
from relatpy import *


def gamma(v):
    return 1/np.sqrt(1-v**2)


def rindler_tau(t, v, g, a):
    return np.log((t * a + g * v + np.sqrt(t**2 * a**2 + 2 *
                                           t * a * g * v + g**2)) / (g * (v + 1))) / a


def rindler_x(v, g, a, tau, x):
    return g / (2 * a) * ((1 + v) * np.exp(a * tau) +
                          (1 - v) * np.exp(-a * tau) - 2) + x


def rindler_t(v, g, a, tau):
    return g / (2 * a) * ((1 + v) * np.exp(a * tau) -
                          (1 - v) * np.exp(-a * tau) - 2 * v)


dt = 0.01
T = 10

# initial conditions #
x1 = 0
v1 = -.9
a1 = 1
d2 = 1
######################
g1 = gamma(v1)
x2 = x1 + d2 / g1
a2 = 1 / (1 / a1 + d2)
u2 = v1*g1 * a2/a1
v2 = u2 / np.sqrt(1+u2**2)
g2 = gamma(v2)

time = np.arange(0, T, dt)

body = Body(vec3(0, x1, 0), vel2(v1, 0), vec2(a1, 0))
body.addPoint(vec2(d2, 0))
point = body.getPoints()[0]

integrator = Integrator(Frame())
integrator.addPoint(body)

t = np.arange(0, T, dt)
steps = t.size
bx = np.zeros(steps)
px = np.zeros(steps)

for i in range(steps):
    bx[i] = body.pos.x
    px[i] = point.pos.x
    integrator.step(dt)

tau1 = np.linspace(0, rindler_tau(T, v1, g1, a1), steps)
tau2 = np.linspace(0, rindler_tau(T, v2, g2, a2), steps)

rindler_x1 = rindler_x(v1, g1, a1, tau1, x1)
rindler_t1 = rindler_t(v1, g1, a1, tau1)
rindler_x2 = rindler_x(v2, g2, a2, tau2, x2)
rindler_t2 = rindler_t(v2, g2, a2, tau2)

plt.plot(bx, t, label="1")
plt.plot(px, t, label="2")
plt.plot(t, t, 'gray', linestyle='dashed', alpha=0.5)
plt.plot(rindler_x1, rindler_t1, label="rindler1", linestyle="dotted")
plt.plot(rindler_x2, rindler_t2, label="rindler2", linestyle="dotted")
plt.grid()
plt.legend()
plt.show()
