
class Subsets:
    def get_subsets(self, nums):
        ans = []
        res = set()


        def fun(index: int, ds):
            if index == len(nums):
                ds.sort()
                res.add(tuple(ds))
                return
            ds.append(nums[index])
            fun(index + 1, ds)
            ds.pop()
            fun(index + 1, ds)
        fun(0, [])
        for it in res:
            ans.append(list(it))
        return ans

s = Subsets()
lst = [4,5,6]
print(s.get_subsets(lst))