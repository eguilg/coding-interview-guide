# 两个单链表相交的一系列问题

【题目】输入的两个单链表可能有环、也可能无环，可能相交也可能不相交。如果相交，返回相交的第一个节点，不相交返回NULL。

【要求】O(N)时间。

【难度】神

```cpp
struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};
```
## 方案一

该问题需要拆分成三个子问题：
1. 判断单链表是否有环，若有，返回环入口，没有则返回NULL。
2. 判断两个无环链表是否相交，若相交，返回第一个交点，不相交返回NULL。
3. 判断两个有环链表是否相交，若相交，返回第一个交点，不相交返回NULL。

### 问题1
对于问题1，如果链表无环，遍历一定可以走到终点，若有环，则不行。

* 若设置两个指针，一快一慢，快的每步前进两个节点，慢的每步前进一个节点，循环遍历下去。如果链表有环，那么这两个指针一定会在某处相遇；如果链表无环，则快指针会走到链表的末尾。

* 判断链表是否有环之后，如果有环，需要找到环的入口。我们假设有环链表在进入环之前有`K`个节点，环有`C`个节点，设上一步中快慢指针相遇的节点是第`x`个节点，那么`x`满足：`2x = x + nC`，即 `x = nC`， 其中`n=1,2...`，所以这时从快慢指针相遇的节点再前进`K`步，就一共走了`x+K = K + nC`，即走过了入环之前的节点，然后在环里转了`n`圈，回到了入环节点。我们可以让一个指针从head开始，另一个从快慢指针相遇处开始，一起前进，他们第一次相遇的节点就是入环口。

```cpp
Node* getLoopNode(Node* head)
{
    if (!head || !head->next){
        return head;
    } 
    Node* slow = head->next;
    Node* fast = head->next->next;
    while (fast && fast->next && fast != slow){
        fast = fast->next->next;
        slow = slow->next;
    } 
    if (fast != slow){
        return NULL;
    }
    fast = head;
    while (fast != slow){
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
```
### 问题2
对于问题2，如果两个链表相交，则末尾一定有一段是相同的。
```cpp
Node* noLoopIntersect(Node* head1, Node* head2, Node* co_tail=NULL){
    if (!head1 || !head2){
        return NULL;
    }
    int len1 = 1, len2 = 1;
    Node* cur1 = head1;
    Node* cur2 = head2;
    while(cur1->next != co_tail){
        cur1 = cur1->next;
        len1++;
    }
    while(cur2->next != co_tail){
        cur2 = cur2->next;
        len2++;
    }
    if (cur1 != cur2){
        return co_tail;
    }
    if (len1 > len2){
        for (int i = 0; i < len1 - len2; ++i){
            head1 = head1->next;
        }
    }  else {
        for (int i = 0; i < len2 - len1; ++i){
            head2 = head2->next;
        }
    } 
    while (head1 != head2){
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1;
}
```
### 问题3
对于问题3，两个链表都有环，

* 两个入环点相同，那么交点会在入环点或者入环点之前，那么解决方法与问题2一样，只是末尾节点从NULL变成了公共的入环点。
* 两个入环点不同，那么从其中一个入环点能够到达另一个，则他们相交，返回其中一个入环点即可。如果从一个入环点不能到达另一个，那么他们不相交，是两个环。

```cpp
Node* loopIntersect(Node* head1, Node* loop1, Node* head2, Node* loop2){
    // 入环点相同，则问题变为求入环之前的第一个交点，跟问题二一致
    if (loop1 == loop2){
        return noLoopIntersect(head1, head2, loop1);
    } 
    // 入环点不同，则看从loop1能否到达loop2
    Node* cur = loop1->next;
    while (cur != loop1 && cur != loop2){
        cur = cur->next;
    }
    if (cur == loop1){ //回到了loop1,说明没相交
        return NULL;
    } else {
        return loop1;   // 找到了loop2，说明相交了，返回loop1 loop2均可
    } 
}
```

### 汇总

* 先分别判断两个链表是否有环。
* 如果都没有环，则是问题2。
* 如果一个有环，一个没环，直接返回NULL。
* 两个都有环，则是问题3.
```cpp
Node* getIntersectNode(Node* head1, Node* head2){
    Node* loop1 = getLoopNode(head1);
    Node* loop2 = getLoopNode(head2);

    if (!loop1 && !loop2){
        return noLoopIntersect(head1, head2);
    } else if (loop1 && loop2){
        return loopIntersect(head1, loop1, head2, loop2);
    }  
    return NULL; 
}
```

