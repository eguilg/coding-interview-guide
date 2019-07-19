# 单双链表中删除倒数第K个节点
【题目】分别实现删除单链表、双链表中的倒数第K个节点。

【要求】O(N)时间。

【难度】狼

```cpp
struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
};

struct biNode{
    int val;
    biNode* next;
    biNode* prev;
    biNode(int x): val(x), next(NULL), prev(NULL){}
};
```
## 方案一
首先，非法输入的判断
* 链表为空
* K < 1

设链表长度为```N```，那么要删除的节点的下标应该是```N-K```(0开始)。
1. ```N - K < 0```时，不存在倒数第K个节点。
2. ```N - k == 0```时，删除的就是头节点。
3. ```N - K > 0```时，删除下标为```N-K```的节点。

对于情况2，直接删除头节点，返回```head->next```即可。

对于情况3，则需要先找到待删除节点的前驱，即下标为```N-K-1```的节点。

遍历一遍链表，每走一步对```K```减一，最后的K就是```K-N```，这时我们再从头遍历，一步一加将其加回0即可找到```N-K```节点。


```cpp
Node* removeLastKth(Node* head, int K){
    if (!head || K < 1){
        return head;
    }
    Node* cur = head;

    while (cur){
        K--;
        cur = cur->next;
    }
    // 此时的 K 为 K-N
    if (K == 0){ // N - K == 0
        head = head->next;
    }
    // N - K > 0
    if (K < 0){
        cur = head;
        while(++K != 0){ // 再往后走一步就是第N - K个节点时停下
            cur = cur->next;
        }
        cur->next = cur->next->next;
    }
    return head;
}


biNode* removeLastKth(biNode* head, int K){
    if (!head || K < 1){
        return head;
    }
    biNode* cur = head;

    while (cur){
        K--;
        cur = cur->next;
    }
    // 此时的 K 为 K-N
    if (K == 0){ // N - K == 0, 删除头节点
        head = head->next;
        head->prev = NULL;
    }
    // N - K > 0
    if (K < 0){
        cur = head;
        while(++K != 0){ // 再往后走一步就是第N - K个节点时停下
            cur = cur->next;
        }
        cur->next = cur->next->next;
        if(cur->next){ // 需要判断被删除节点的next是否为空，若为空则不能修改其prev
            cur->next->prev = cur;
        }
    }
    return head;
}
```

## 方案二
快慢指针的方法，先定义一个```fast```指针和```slow```指针，让前者先走```K```步，然后两个指针一起往后走，当```(!fast->next)```的时候的```slow```就是待删除的前一个节点。

当然还要考虑N < K和N == K的情况。

然而这方法并不是人们所说的one pass，实际上跟上一个方法没什么区别。

```cpp
Node* removeLastKth2(Node* head, int K){
    if (!head || K < 1){
        return head;
    }
    Node* fast = head, *slow = head;
    while(K && fast){
        fast = fast->next;
        K--;
    } 
    if (!fast && K == 0){
        head = head->next;
    } else if (K == 0){
        while(fast->next){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
    }
    return head; 
}
```