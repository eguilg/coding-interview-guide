n, k = list(map(int, input().split()))
heights = list(map(int, input().split()))

ans = 0
cur_h = 0
for i in range(k):
    cur_h += heights[i]
min_h = cur_h 
for i in range(k, n):
    cur_h += heights[i] - heights[i-k]
    if cur_h < min_h:
        min_h = cur_h
        ans = i-k+1 
print(ans+1)
