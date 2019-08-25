"""
median-of-three quick sort

""" 
def median(a, b, c, key=None): 
    if not key:
        key = lambda x: x
    if key(a) < key(b):
        if key(b) < key(c):
            return b
        elif key(c) < key(a):
            return a
        else:
            return c
    else:
        if key(c) < key(b):
            return b
        elif key(a) < key(c):
            return a
        else:
            return c

def partition(arr, l, r, pivot, key=None):
    
    print(arr, pivot)
    if not key:
        key = lambda x: x
    while True:
        while (key(arr[l]) < key(pivot)):
            l += 1
        r -= 1
        while (key(pivot) < key(arr[r])):
            r -= 1
        if (l >= r): 
            print(l,r)
            return l
        arr[l], arr[r] = arr[r], arr[l]
        l += 1

def qsort(arr, l, r, key=None):
    if not key:
        key = lambda x: x
    if r - l < 2 :
        return  
    mid = l + (r - l) // 2
    pivot = median(arr[l], arr[r-1], arr[mid], key)
    p = partition(arr, l, r, pivot, key)
    
    qsort(arr, l, p, key)
    qsort(arr, p, r, key)
    return

def quick_sort(arr, key=None):
    if not key:
        key = lambda x: x
    qsort(arr, 0, len(arr), key)
    return

if __name__ == '__main__':
    a = [2,3,4,7,8,9,1,13,4,4,3,2,1]
    quick_sort(a, key=lambda x: -x)
    print(a)
    
             
        
    
