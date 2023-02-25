lst = list([2,3,-4,-5,6])
pos = neg = 0

for ele in lst:
    if ele > 0:
        pos += 1
    elif ele < 0:
        neg += 1

print(neg, " ", pos)