import matplotlib.pyplot as plt
import numpy as np
import relatpy as rp



N = 100
T = np.linspace(0,10, N)
X = np.zeros(N)

frame = rp.Frame()
point = rp.PointWorldline(frame)


for i, t in enumerate(T):
    vec = point.integrate(t)
    X[i] = vec.x

plt.plot(X,T)
plt.show()