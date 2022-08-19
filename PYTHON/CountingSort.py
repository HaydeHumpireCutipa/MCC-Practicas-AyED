#COUNTING SORT
def countSort(arr):
    output = [0 for i in range(len(arr))]
    count = [0 for i in range(256)]
    ans = [0 for i in arr]

    for i in arr:
        count[i] += 1
 
    for i in range(256):
        count[i] += count[i-1]
 
    for i in range(len(arr)):
        output[count[arr[i]]-1] = arr[i]
        count[arr[i]] -= 1
 
    for i in range(len(arr)):
        ans[i] = output[i]
    return ans
