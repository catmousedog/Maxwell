import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.widgets import Slider
import numpy as np
from relatpy import *

# Define a function to apply your custom transformation to a set of points
def custom_transform(points, vx, vy):
    vel = vel2(vx, vy)
    t_points = []
    for p in points:
        vec = vec3(p[0], p[1], p[2])
        boosted = vec.boosted_vec(vel)
        t_points.append([boosted.t, boosted.x, boosted.y])
        
    return np.array(t_points)

# Define parameters for the line
start_point = np.array([-1., 0, 0])
end_point = np.array([1., 0, 0])
num_points = 10  # Number of points along the line

# Calculate points along the line
alpha_values = np.linspace(0, 1, num_points)
points_on_line = []

for alpha in alpha_values:
    point = (1 - alpha) * start_point + alpha * end_point
    points_on_line.append(point)

# Convert the list of points to a NumPy array
points = np.array(points_on_line)

# Create initial values for vx and vy
vx_initial = 0.0
vy_initial = 0.0

# Create a figure with 3D scatter plot and sliders
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
plt.subplots_adjust(left=0.25, bottom=0.25)

# Define the sliders' positions and sizes
ax_vx = plt.axes([0.25, 0.01, 0.65, 0.03])
ax_vy = plt.axes([0.25, 0.06, 0.65, 0.03])

# Create the sliders
slider_vx = Slider(ax_vx, 'vx', -0.99, .99, valinit=vx_initial)
slider_vy = Slider(ax_vy, 'vy', -0.99, .99, valinit=vy_initial)

# Function to update the plot when sliders change
def update(val):
    vx = slider_vx.val
    vy = slider_vy.val

    ax.cla()  # Clear the existing plot

    # Apply the custom transformation to the points with updated vx and vy
    transformed_points = custom_transform(points, vx, vy)

    # Extract coordinates for plotting
    t_vals = transformed_points[:, 0]
    x_vals = transformed_points[:, 1]
    y_vals = transformed_points[:, 2]

    # Plot the transformed points in red
    ax.scatter(x_vals, y_vals, t_vals, color='red', label='Transformed Points')

    # Extract coordinates for the original points
    t_vals_orig = points[:, 0]
    x_vals_orig = points[:, 1]
    y_vals_orig = points[:, 2]

    # Plot the original points in blue
    ax.scatter(x_vals_orig, y_vals_orig, t_vals_orig, color='blue', label='Original Points')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('T')
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_zlim(-2, 2)

    ax.legend()

    plt.draw()

# Attach the slider update function to the slider events
slider_vx.on_changed(update)
slider_vy.on_changed(update)


# Initial plot
update(None)

plt.show()
