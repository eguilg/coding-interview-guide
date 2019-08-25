"""
1. 一个数二进制中有多少1
2. 滑动窗口中的最大值
3. 行列分别有序的矩阵中第k大的数
给二叉树前序，重构二叉树 * 3
4. 旋转矩阵中查找
5. 多个字符串中所有的唯一的前缀
6. 3sum, closest 3sum, 4 sum
7. 字符串中第一个不重复字符
8. 二维平面N个点中求最大斜率
9. 逆时针打印数组
10. 给先序遍历重构二叉树（124XXX3XX）
11. 判断平面内的线段是否相交？
12. 机器人从左上角走到右下角的走法
13. 给定n，用1到n作为二叉搜索树的节点值，返回n个点所能组成的二叉搜索树的个数
14. 大数乘法 减法
15. 字符串split
16. 寻找数组的最短连续子数组的长度，使得子数组的和大于等于t。
17. 给定一个大小为n*3的木板，问用大小为1*3的木板进行填充，有多少种填充方法
18. 求递增数组的最长子序列长度，要求子序列满足斐波那契数列
19. 最小覆盖子串 给字符串 S、一个字符串 T，在S 中找出包含 T 所有字母的最小子串。



非编程
1. 用随机数0-2 0-3 0-4构建100的随机数
2. 49个人中至少几个人生日是同一月
3. 两个人只握一次手，一共握了45次，问一共几个人（10）
4. 两个年级同学的身高数据，正态的，怎么判断数据是相同的分布？
5. 1个正反面、2个全正面、2个全反面，随机取一个硬币抛是正面，另一面也是正面的概率
"""

"""
1. 一个数二进制中有多少1
"""
def countOneInBinary(x : int):
    count = 0
    while (x):
        x = x & (x-1)
        count += 1
    return count
print(countOneInBinary(9))

"""
2. 滑动窗口中的最大值
"""
from collections import deque
def maxInWindow(arr: list, k: int):
    if not arr or k < 1:
        return []
    if k >= len(arr):
        return [max(arr)]
    ans = []
    dq = deque()
    for i in range(len(arr)):
        while len(dq) != 0 and arr[dq[-1]] < arr[i]:
            dq.pop()
        dq.append(i)
        while len(dq) != 0 and i - dq[0] + 1 > k:
            dq.popleft()
        if i >= k - 1:
            ans.append(arr[dq[0]])
    return ans

print(maxInWindow([2,1,7,3,6,9,1,3], 2))

"""
3. 行列分别有序的矩阵中第k大的数
"""
from heapq import heapify, heappop, heappush
def maxKthInMat(mat, k):
    if mat is None or k < 1:
        return None
    n , m = len(mat), len(mat[0])
    hp = []
    for i in range(n-1, -1, -1):
        if len(hp) == k:
            break
        heappush(hp, (mat[i][-1], i, m-1)) 
    for i in range(n-1, max(-1, n-k-1), -1):
        j = m - 2
        while j >= 0:
            if len(hp) == k and mat[i][j] > hp[0][0]:
                heappop(hp) 
            if len(hp) < k:
                heappush(hp, (mat[i][j], i, j))
            j -= 1
    return hp[0][0]
import numpy as np
a = np.random.random((500,500))
print(a)
print(maxKthInMat(a, 62500))
    
        
        
        




