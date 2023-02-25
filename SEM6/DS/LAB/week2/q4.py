lst = list([2,3,4,5,6])

for i in range(len(lst)):
    if lst[i]%2 == 0:
        del lst[i]

print(lst)