
"""
2048游戏，4*4地图，1 2 3 4 上下左右，给滑动方向和初始状态，求一次滑动后的结果
"""
dir = int(input())

mat = []
for _ in range(4):
    mat.append(list(map(int, input().split())))

if dir == 1: # 上
    for i in range(4): 
        for j in range(4): 
            if j != 3 and mat[j][i] == mat[j+1][i]:
                mat[j][i] *= 2
                mat[j+1][i] = 0 

        for j in range(4):
            if mat[j][i] == 0:
                continue
            k = j
            while k != 0 and mat[k-1][i] == 0:
                mat[k-1][i] = mat[k][i]
                mat[k][i] = 0
                k -= 1

elif dir == 2:
    for i in range(4): 
        for j in range(3, -1, -1): 
            if j != 0 and mat[j][i] == mat[j-1][i]:
                mat[j][i] *= 2
                mat[j-1][i] = 0 

        for j in range(3, -1, -1):
            if mat[j][i] == 0:
                continue
            k = j
            while k != 3 and mat[k+1][i] == 0:
                mat[k+1][i] = mat[k][i]
                mat[k][i] = 0
                k += 1
elif dir == 3:
    for i in range(4): 
        for j in range(4): 
            if j != 3 and mat[i][j] == mat[i][j+1]:
                mat[i][j] *= 2
                mat[i][j+1] = 0 

        for j in range(4):
            if mat[i][j] == 0:
                continue
            k = j
            while k != 0 and mat[i][k-1] == 0:
                mat[i][k-1] = mat[i][k]
                mat[i][k] = 0
                k -= 1
else:
    for i in range(4): 
        for j in range(3, -1, -1): 
            if j != 0 and mat[i][j] == mat[i][j-1]:
                mat[i][j] *= 2
                mat[i][j-1] = 0 

        for j in range(3, -1, -1):
            if mat[i][j] == 0:
                continue
            k = j
            while k != 3 and mat[i][k+1] == 0:
                mat[i][k+1] = mat[i][k]
                mat[i][k] = 0
                k += 1

for line in mat:
    print(' '.join(list(map(str, line)))) 
