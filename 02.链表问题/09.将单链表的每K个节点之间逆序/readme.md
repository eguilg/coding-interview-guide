# 将单链表的每K个节点之间逆序

【题目】给定一个单链表的头节点head，实现一个调整单链表的函数，使得每K个节点之间逆序，如果最后不够K个节点一组，则不调整最后几个节点。

【要求】O(N)时间。

【难度】虎

```cpp
struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};
```

## 方案一
用栈
```cpp
Node* reverseKNodes1(Node* head, int k){
    if (k < 2){
        return head;
    }
    stack<Node*> s;
    Node* newHead = head;
    Node* pre = NULL, * cur = head, *nxt = NULL;
    while(cur != NULL){
        nxt = cur->next;
        s.push(cur);
        if (s.size() == K){
            while (!s.empty()){
                if (!pre){
                    newHead = s.top();
                    pre = newHead;
                } else {
                    pre->nxt = s.top();
                    pre = pre->nxt;
                }
                s.pop();
            }
        }
        cur = nxt; 
    }
    return newHead;
}
```

## 方案二
边遍历边反转。
```cpp
/*
反转从[head, end)区间内的链表节点，并将反转后的头尾与pre、end连接 
返回新的头
 */
Node* reverse_part_list(Node* head, Node* pre=NULL, Node* end=NULL){
    Node* nxt = NULL;
    while(head != end){
        nxt = head->next;
        head->next = pre;
        pre = head;
        head = nxt;
    }
    return pre;
}

Node* reverseKNodes2(Node* head, int k){
    if (k < 2){
        return head;
    } 
    Node* cur = head, *pre = NULL, *nxt = head;
    int count = 0;
    while (cur){
         nxt = cur->next;
         if (count == k){
             if (pre){
                 pre->next = reverse_part_list(pre->next, NULL, nxt);
             } else{
                 pre = head;
                 head = reverse_part_list(head, NULL, nxt);
                 pre->next = nxt;
             }
         }
         count++;
         cur = nxt;
    }
    return head;
}
```