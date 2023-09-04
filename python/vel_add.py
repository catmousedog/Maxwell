import matplotlib.pyplot as plt
import numpy as np
from relatpy import *
import copy

def printv(v):
    print(f"({v.vx()},{v.vy()})")

frame = Frame()
point = PointWorldline(frame)

v = vel2(0.5, 0.1)
u = vel2(0.3, 0.2)

fig, ax = plt.subplots()

# Create a circle with radius 1
circle = plt.Circle((0, 0), 1, fill=False)
ax.add_artist(circle)

# Function to handle mouse click events
def on_click(event):
    global v, u

    if event is not None:
        if event.button == 1:  # Left-click to update v
            v = vel2(event.xdata, event.ydata)
        if event.button == 2:  # Left-click to update v
            v, u = u, v
        elif event.button == 3:  # Right-click to update u
            u = vel2(event.xdata, event.ydata)

    ax.clear()

    # Add the circle again
    ax.add_artist(circle)

    # Plot v, u, and v + u
    plt.scatter(v.vx(), v.vy(), label="v", color='blue')
    plt.scatter(u.vx(), u.vy(), label="u", color='red')

    uv = vel2(v)
    uv.boosted_vel(u)
    plt.scatter(uv.vx(), uv.vy(), label="v + u", color='green')

    plt.legend()
    plt.xlim(-1, 1)
    plt.ylim(-1, 1)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.draw()

# Connect the click event handler
cid = fig.canvas.mpl_connect('button_press_event', on_click)

on_click(None)

plt.xlim(-1, 1)
plt.ylim(-1, 1)
plt.gca().set_aspect('equal', adjustable='box')

plt.show()
