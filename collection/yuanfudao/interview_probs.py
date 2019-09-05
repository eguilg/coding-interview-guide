"""
作者：stitchohana
链接：https://www.nowcoder.com/discuss/236679
来源：牛客网

1.栈排序
2.链表实现队列
3.最长连续递增序列
4.最长不连续序列
** 5.二维数组回行打印 **
6.无序数组构建一棵二叉排序树
7.一个数组实现两个栈
** 8.二叉树宽度 **
9.二叉树是否对称
10.链表m到n反转
11.一个n位数，现在可以删除其中任意k位，使得剩下的数最小
12.实现有符号大数链表加法，靠近头结点位置为高位
13.字符串横向改纵向
14.八皇后的问题
15.找出来数组中每个元素后边第一个比它大的值
** 16.给你一个二叉树，从上往下看，然后左往右顺序输出你能看到节点，同一个竖直方向上上面的节点把下面的节点遮挡住了
** 17.链表反转，分别用遍历与递归实现
18.完全二叉树的最大深度与节点个数
19.两个栈实现队列
20.两个有序数组交集、并集
21.给定一个有序存在重复的值链表，使得每个元素只出现一次
22.leetcode 200
23.二叉搜索树转有序双向链表
24.字符串全排列 ，可能有重复的，要去重
25.二叉搜索树第k个节点，不用中序遍历
26.有序数组查找重复元素个数
27.定长数组实现队列
28.用二分法对一个数字开根号
29.判断一颗树是不是二叉搜索树
30.Excel表的列字母转换，输入第几列，输出列字母组合
31.链表第k-1个节点
** 32.手撕快排
33.二分查找
34.一个无序有正有负数组，求乘积最大的三个数的乘积
35.求二叉树的深度，不使用递归
36.实现链表，无序链表，对链表值奇偶分离并排序，空间复杂度O(1)
37.单调不递减数组，给一个target，找出大于等于target的下标index
38.单调不递减链表，删除掉重复值
39.无序数组构建一棵二叉排序树
40.行和列都是有序的二维矩阵找一个target值
** 41.是否是回文链表
42.打印出根节点到叶子节点的最长路径
43.双链表按照奇偶顺序分成两个链表，要求不要复制链表
44.不严格递增数组，要求删除出现次数大于k的数字，要求不要新建存储空间
45.链表相邻元素交换
46.二叉树的最小公共祖先
47.字符串形式自定义进制大数相加
48.链表每隔k个反转
49.输出根节点到叶子节点路径之和为target的路径列表
50.一些数，任意排列求可形成最小的值
51.LeetCode  1038.
52.数组题，任意一个整型数组，判断是否可以将数组分为三个区间，每个区间中数值的和相同
53.已排序的整数数组去重
** 54.错位的全排列（第一位不能是1，第二位不能是2）
55.k路链表归并 -> 堆
56.非降序数组，找与target最相近的数的下标
57.二叉树逆时针打印最外层节点
58.输入一个数字n，构建一个完全二叉树并输出
59.输入一个矩阵，起始点和目标点，判断是否存在可达路径
60.无向图最短路径
61.第K层叶子节点个数
"""


#######################重复题#######################
"""
5. 二维数组回行打印
思路： 分层打印 (x1, y1) 和 (x2, y2)
"""

def printMatrix(mat):
    X = len(mat)
    if X == 0:
        return
    Y = len(mat[0])
    if Y == 0:
        return
    
    x1, y1, x2, y2 = 0, 0, X-1, Y-1
    while x1 <= x2 and y1 <= y2:
        cur_x, cur_y = x1, y1
        dx, dy = 0, 1
        while True:
            print(mat[cur_x][cur_y], end="")
            if cur_x + dx > x2 or cur_x + dx < 0 or cur_y + dy > y2 or cur_y + dy < 0:
                dx, dy = dy, -dx # 向量旋转的方法
            cur_x += dx
            cur_y += dy
            if (cur_x == x1 and cur_y == y1) or (cur_x > x2 or cur_x < 0 or cur_y > y2 or cur_y < 0): 
                if x1 + 1 <= x2 - 1 and y1 + 1 <= y2 - 1:
                    print(" ", end="")
                else:
                    print("")
                break
            else:
                print(" ", end="")
        x1 += 1
        y1 += 1
        x2 -= 1
        y2 -= 1
    
printMatrix([[1, 2, 3]])

"""
8.二叉树宽度
思路：层次遍历
"""
from queue import Queue

def treeWidth(root):
    if not root:
        return 0
    q = Queue()
    q.put(root)
    max_w = 1
    while q:
        cur_w = len(q)
        max_w = max(cur_w, max_w)
        for _ in range(cur_w):
            node = q.get()
            if node.left:
                q.put(node.left)
            if node.right:
                q.put(node.right)
    return max_w

"""
反转链表
"""
class Node:
    def __init__(self, n):
        self.val = n
        self.next = None

def reverseLinklist(head):
    if not head or not head.next:
        return head
    tail = head.next
    newHead = reverseLinklist(head.next)
    tail.next = head
    head.next = None
    return newHead

def reverseLinklist2(head):
    if not head or not head.next:
        return head
    prev = None
    cur = head
    while cur:
        nxt = cur.next
        cur.next = prev
        prev = cur
        cur = nxt
    return prev

head = Node(0)
head.next = Node(1)
head.next.next = Node(2)
head = reverseLinklist2(head)
while head:
    print(head.val)
    head = head.next

"""
快排
"""
def qsort(arr, begin, end):
    if begin >= end:
        return
    l, r = begin, end
    p = arr[l]
    while l < r:
        while l < r and arr[r] >= p:
            r -= 1
        arr[l] = arr[r]
        while l < r and arr[r] <= p:
            l += 1
        arr[r] = arr[l]
        arr[l] = p
    
    qsort(arr, begin, l-1)
    qsort(arr, l+1, end)
    return arr

print(qsort([1,7,2,4,3], 0, 4))


"""牛顿法开根号"""
def newton(num): 
    cur = 1
    eps = 1e-4
    nxt = 0
    while abs(nxt**2 - num) > eps:
        nxt = (cur + num/cur) * 0.5 
        cur = nxt
    return nxt
print(newton(1.1))
#######################重复题#######################