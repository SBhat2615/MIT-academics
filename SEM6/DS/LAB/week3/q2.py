import numpy as np

A = np.array([
    [2,3],
    [5,6]
])


print(A.sum(axis=1))
print(A.sum(axis=0))