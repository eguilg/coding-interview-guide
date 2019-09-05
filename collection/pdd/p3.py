"""
输入
第一行n 色子个数
第二行n个数代表每个色子面数
求所有色子的结果的最大值的期望

"""

n = int(input())
faces = list(map(int, input().split()))

p = [0] * 51
for f in faces:
    for i in range(1, f+1):
        if p[i] == 0:
            p[i] = 1
        p[i] *= (i / f) 
E = 0 
for i in range(1, len(p)): 
    if p[i] == 0:
        break 
    E += i * (p[i] - p[i-1]) 

print("%.2f"% E) 