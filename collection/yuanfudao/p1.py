C = int(input())
for _ in range(C):
    P = list(map(int, input().split())) 
    P = P[1:] 
    top1, top2 = 0, 0
    s = 0
    for n in P:
        s += n
        if n > top1: 
            top2 = top1
            top1 = n
        elif n > top2:
            top2 = n 
    if s - top1 - top2 >= top1:
        print(s // 3)
    else:
        print(s - top1 - top2)
