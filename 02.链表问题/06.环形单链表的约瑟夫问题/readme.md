# 环形单链表的约瑟夫问题

【题目】输入一个环形链表head，和报数次数m，一开始从head开始报数，每次将报数为m的节点移除，然后从被移除的下一个节点开始继续。返回最后剩下的节点。

【要求】O(N)时间。

【难度】鬼

## 方案一

直接模拟。

```cpp
Node* josephusKill1(Node* head, int m){
    if (!head || head->next == head || m < 1){
        return head;
    }
    Node* last = head;
    int left_num = 1;
    while (last->next != head){
        last = last->next;
        left_num += 1;
    }
    int mm = (m-1) % left_num;
    while (left_num != 1){
        // 找到自杀节点head
        while (mm-- != 0) {
            last = head;
            head = head->next; 
        }
        last->next = head->next;
        head = last->next;
        left_num--;
        mm = (m-1) % left_num;
    } 
    return last;
}
```

## 方案二

重点在找到每次删除节点前后节点索引编号的递推关系。

* 假设在环的节点数为`i`时的索引编号为从`1`到`i`，其中第`s`号索引报号为`m`，要被移除，则有`s = (m-1)%i + 1`。
* 接下来环的节点还剩`i-1`个，从上一步中的`s`号节点的后面一个节点开始，新的索引编号为从`1`到`i-1`。

两个环节点数不同的状态各自的节点编号关系对应如下：

|节点数`i`|节点数`i-1`|  
|---|---|
|s-2|i-2|
|s-1|i-1|
|s|deleted|
|s+1|1|
|s+2|2|
|...|...|

我们可以得到，如果一个节点在环数`i`时编号为`idx(i)`，环数`i-1`时编号为`idx(i-1)`，那么有

`idx(i) = (idx(i-1)+s-1)%i + 1`

将`s = (m-1)%i + 1`带入得，

`idx(i) = (idx(i-1) + (m - 1)%i) % i + 1`

而且我们知道，最后剩下1个节点的时候，`idx(1)=1`，我们要知道这个环节点数为`1`时候的`1`号节点，在最开始`N`个节点的时候对应的编号，所以我们只要一路递推到`idx(N)`就好了。

时间复杂度`O(N)`

```cpp
Node* josephusKill2(Node* head, int m)
{
    if (!head || head->next == head || m < 1){
        return head;
    } 
    int i = 1, cur_num = 1;
    Node* cur = head;
    while (cur->next != head){
        i++;
        cur_num = (cur_num + (m-1)%i) % i + 1;
        cur = cur->next;
    }
    cur = head; 
    while (--cur_num){
        cur = cur->next;
    }
    return cur; 
}
```