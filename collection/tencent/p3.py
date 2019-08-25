n, q = map(int, input().split())
w = list(map(int, input().split()))
v = list(map(int, input().split()))

ret = 0
l, r = 1, int(1e13)
while l <= r:
    mid = l + (r - l) // 2
    cur_s = 0
    for i in range(n):
        cur_s += max(mid - w[i], 0) * v[i]
        if cur_s > q:
            break
    if cur_s > q:
        r = mid - 1
    else:
        l = mid + 1
        ret = max(mid, ret)
print(ret)