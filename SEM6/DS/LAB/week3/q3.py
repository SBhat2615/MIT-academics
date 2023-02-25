import numpy as np

# a)
arr = list([2,3,4,5])
a = np.array(arr)
print(a, type(a), sep='\n')

# b)
arr = tuple([2,3,4,5])
a = np.array(arr)
print(a, type(a), sep='\n')

# c)
arr = np.zeros((3,4))
print(arr)

# d)
arr = np.arange(0, 20, 5)
print(arr)

# e)
arr = np.array([
    [2,3,4,8],
    [5,3,6,2],
    [2,6,7,1]
])
print(arr.reshape((2,2,3)))

# f)
arr = np.array([
    [2,3,4,8],
    [5,3,6,2],
    [2,6,7,1]
])
print(np.max(arr))
print(np.min(arr))

print()

for row in arr:
    print(np.max(row))
    print(np.sum(row))
print()

for row in arr.transpose():
    print(np.max(row))
    print(np.sum(row))


