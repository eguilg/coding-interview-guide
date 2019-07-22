# 判断链表是否为回文

【题目】输入一个环形链表head，和报数次数m，一开始从head开始报数，每次将报数为m的节点移除，然后从被移除的下一个节点开始继续。返回最后剩下的节点。

【要求】O(N)时间。

【难度】狼

## 方案一
先全部入栈，然后一遍出栈一边遍历原链表看是否全部相同。
```cpp
bool isPalindromel1(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* cur = head;
    while (cur){
        s.push(cur);
        cur = cur->next;
    }
    cur = head;
    while (!s.empty() && cur){
        if (s.top()->val != cur->val){
            isP = false;
            break;
        }
        s.pop();
        cur = cur->next;
    }
    return isP;
}
```

## 方案二
只用入栈右半部分。
```cpp
bool isPalindromel2(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* cur = head, *right = head;
    while (right->next && right->next->next){
        right = right->next->next;
        cur = cur->next;
    }
    while(cur->next){
        s.push(cur->next);
        cur = cur->next;
    }
    cur = head;
    while (!s.empty() && cur){
        if (s.top()->val != cur->val){
            isP = false;
            break;
        }
        s.pop();
        cur = cur->next;
    }
    return isP;
} 
```

## 方案三
将后半部分链表反转，然后从两头向中间遍历，判断是否一直相等，最后再把后半部分还原。
```cpp
bool isPalindromel3(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* mid = head, *right = head;
    while (right->next && right->next->next){
        right = right->next->next;
        mid = mid->next;
    }
    // mid是后半部分的前一个节点，反转后半部分
    Node* rightStart = reverse_list(mid->next, mid);
    // 中间节点的next设为空，用来停止循环遍历
    mid->next = NULL;
    // 左边的头
    Node* left = head;
    // 右边的头
    right = rightStart;
    // 判断是否两头都相同
    while(left){
        if (left->val != right->val){
            isP = false;
            break;
        }
        left = left->next;
        right = right->next;
    }
    // 还原链表的后半部分
    reverse_list(rightStart);
    return isP;
} 
```
给定头部、前驱、结束位置，反转部分链表的函数：
```cpp
Node* reverse_list(Node* head, Node* pre = NULL, Node* end = NULL){
    Node* nxt = NULL;
    while(head != end){
        nxt = head->next;
        head->next = pre;
        pre = head;
        head = nxt;
    } 
    return pre;
}
```