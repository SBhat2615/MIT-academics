import numpy as np
A = np.array([
    [2,3],
    [5,6]
])

B = np.transpose(A)

sum = np.add(A,B)

print(sum)