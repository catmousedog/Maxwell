import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.widgets import Slider
import numpy as np
from relatpy import *


def gamma(v):
    return 1/np.sqrt(1-v**2)


dt = 0.001
T = 10

# initial conditions #
x1 = 1
v1 = -.0
g1 = gamma(v1)
a1 = 1
d = 1
######################

x2 = x1 + d / g1
a2 = 1 / (1 / a1 + d)
u2 = v1*g1 * a2/a1
v2 = u2 / np.sqrt(1+u2**2)

time = np.arange(0, T, dt)
frame = Frame()
integrator = Integrator(frame)

body = Body(frame, vec3(0, x1, 0))
body.vel = vel2(v1, 0)
body.accel = vec2(a1, 0)
body.addPoint(vec2(d, 0))

point = body.getPoints()[0]

integrator.addPoint(body)

t = np.arange(0, T, dt)
steps = t.size
pt = np.zeros(steps)
bx = np.zeros(steps)
px = np.zeros(steps)
tau1 = np.zeros(steps)
tau2 = np.zeros(steps)

for i in range(steps):
    integrator.step(dt)
    bx[i] = body.x
    px[i] = point.x
    tau1[i] = body.ptime
    tau2[i] = point.ptime


rindler_x1 = 1 / (2 * a1) * ((1+v1)*np.exp(a1 * tau1) +
                             (1-v1)*np.exp(-a1 * tau1) - 2) + x1
rindler_t1 = 1 / (2 * a1) * ((1+v1)*np.exp(a1 * tau1) -
                             (1-v1)*np.exp(-a1 * tau1) - 2 * v1)
rindler_x2 = 1 / (2 * a2) * ((1+v2)*np.exp(a2 * tau2) +
                             (1-v2)*np.exp(-a2 * tau2) - 2) + x2
rindler_t2 = 1 / (2 * a2) * ((1+v2)*np.exp(a2 * tau2) -
                             (1-v2)*np.exp(-a2 * tau2) - 2 * v2)

plt.plot(bx, t, label="1")
# plt.plot(px, t, label="2")
plt.plot(t, t, 'gray', linestyle='dashed', alpha=0.5)
plt.plot(rindler_x1, rindler_t1, label="rindler1", linestyle="dotted")
# plt.plot(rindler_x2, rindler_t2, label="rindler2", linestyle="dotted")
plt.grid()
plt.legend()
plt.show()
