

def binary_search(arr, low, high, search):
  if low <= high:
      mid = (high + low) // 2
      if arr[mid] == search:
          return mid
      elif arr[mid] > search:
          return binary_search(arr, low, mid - 1, search)
      else:
          return binary_search(arr, mid + 1, high, search)
  else:
      return None
    
if __name__=='__main__':
    lst = list([2,4,5,7,8,9])
    search = 5
    index = binary_search(lst, 0, len(lst)-1, search)
    if index is not None:
      print('Element is present at index : ', index)
    else:
      print('Element not present')