import numpy as np
import matplotlib.pyplot as plt

def mandelbrot(c):
    z = complex(0, 0)
    for i in range(100):
        z = z**2 + c
        if abs(z) > 4:
            return i
    return 100

def mandelbrotSet(x, y):
    m = np.zeros((len(x), len(y)))
    for i, r in enumerate(x):
        for j, c in enumerate(y):
            m[i, j] = mandelbrot(complex(r, c))
    return m

x = np.linspace(-2, 1, 800)
y = np.linspace(-1, 1, 800)
m = mandelbrotSet(x, y)

plt.imshow(m.T, cmap="magma", extent=[-2, 1, -1, 1])
plt.axis("off")
plt.show()
