import numpy as np

A = np.matrix([
    [1, 0, -53.33],
    [0, 1, 0],
    [0, 0, 1]
])

B = np.matrix([
    [0, -1, 0],
    [1, 0, 0],
    [0, 0, 1]
])

C = np.matrix([
    [1, 0, -100],
    [0, 1, -76.67],
    [0, 0, 1]
])

print(np.matmul(np.matmul(C, B), A))
