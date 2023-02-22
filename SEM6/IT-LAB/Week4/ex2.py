class PairSum:
    def pair(self, lst, target):
        
        for i in range(len(lst)):
            for j in range(i):
                if lst[i]+lst[j] == target:
                    return i, j

p = PairSum()
lst = [10,20,10,40,50,60,70]
target = 50
x, y = p.pair(lst, target)
print(x, ',', y)