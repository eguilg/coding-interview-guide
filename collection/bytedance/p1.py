"""
第一行N， 后面是N*N矩阵，代表N个用户间的互动数量，互动数量大于3则有边，求联通域数量
input:
3
0 4 0
4 0 0
0 0 0

output:
2
"""

N = int(input())
mat = []
for _ in range(N):
    mat.append(list(map(int, input().split())))

k = 0
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
                if mat[cur][idx] >= 3 and vis[idx] == 0:
                    stack.append(idx)
        else:
            cur = stack.pop()
    if count:
        k += 1
print(k)