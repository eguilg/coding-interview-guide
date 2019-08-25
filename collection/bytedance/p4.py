"""
输入第二行数字代表节点，如果两个节点的数字最大公约数大于1，则有边，求最大联通块
6
20 50 22 74 9 63

4 
"""

N = int(input())
V = list(map(int, input().split()))

# TODO: 辗转相除法的优化
def gcd(a, b):
    c = a%b
    if c == 0:
        return b
    else:
        return gcd(b, c)

mat = [[0] * N for _ in range(N)]
for i in range(N):
    for j in range(i+1, N):
        if gcd(V[i], V[j]) > 1:
            mat[i][j] = 1
            mat[j][i] = 1

ans = 0
vis = [0 for _ in range(N)]
for seed in range(N):
    if vis[seed] != 0:
        continue
    cur = seed
    stack = []
    count = 0
    while vis[cur] != 1 or len(stack) > 0:
        if vis[cur] != 1:
            vis[cur] = 1
            count += 1
            for idx in range(N):
                if mat[cur][idx] == 1 and vis[idx] == 0:
                    stack.append(idx)
        else:
            cur = stack.pop()
    ans = max(ans, count)
print(ans)