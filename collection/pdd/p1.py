"""
输入 arr;N
输出前N个数字 偶数优先级>奇数，同奇偶的大的优先
555503,772867,756893,339138,399447,40662,859037,628085,855723,974471,599631,636153,581541,174761,948135,411485,554033,858627,402833,546467,574367,360461,566480,755523,222921,164287,420256,40043,977167,543295,944841,917125,331763,188173,353275,175757,950417,284578,617621,546561,913416,258741,260569,630583,252845;10

913416,566480,420256,339138,284578,40662,977167,974471,950417,948135

"""

from heapq import heapify, heappush, heappop

arr, N = input().split(';')
arr = list(map(int, arr.split(',')))
N = int(N) 
if N == 0:
    print('')
hp_e, hp_o = [], []
for num in arr: 
    if num % 2 == 0:
        if len(hp_e) == N and num > hp_e[0]:  
            heappop(hp_e)
        elif len(hp_e) + len(hp_o) == N and len(hp_o) > 0: 
            heappop(hp_o) 
        if len(hp_e) + len(hp_o) != N:
            heappush(hp_e, num)
    else:
        if len(hp_e) + len(hp_o) == N and len(hp_o) != 0 and num > hp_o[0]:
            heappop(hp_o)

        if len(hp_e) + len(hp_o) != N:
            heappush(hp_o, num)
        

num_e, num_o = len(hp_e), len(hp_o)
s_e = list(map(str, reversed([heappop(hp_e) for _ in range(num_e)])))
s_o = list(map(str, reversed([heappop(hp_o) for _ in range(num_o)])))

print(','.join(s_e + s_o))
            