# 反转单向和双向链表

【题目】分别实现反转单向和双向链表。

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

## 解法一

递归

```cpp
Node* reverse_list1(Node* head)
{
    if (!head || !head->next){
        return head;
    }
    Node* newTail = head->next;
    Node* newHead = reverse_list(head->next);
    newTail->next = head;
    head->next = NULL;
    return newHead;
}

biNode* reverse_list1(biNode* head)
{
    if (!head || !head->next){
        return head;
    }
    biNode* newTail = head->next;
    biNode* newHead = reverse_list(head->next);
    newTail->next = head;
    head->prev = newTail;
    head->next = NULL;
    return newHead;
}
```

## 方案二

stack
```cpp
Node* reverse_list2(Node* head){
    if (!head || !head->next){
        return head;
    }
    stack<Node*> s;
    while (head){
        s.push(head);
        head = head->next;
    }
    head = s.top();
    Node *cur = head;
    s.pop();
    while (!s.empty()){
        cur->next = s.top();
        s.pop();
        cur = cur->next;
    }
    cur->next = NULL;
    return head; 
}

biNode* reverse_list2(biNode* head){
    if (!head || !head->next){
        return head;
    }
    stack<biNode*> s;
    while (head){
        s.push(head);
        head = head->next;
    }
    head = s.top(); 
    s.pop();
    head->prev = NULL;
    biNode *cur = head; 
    while (!s.empty()){
        cur->next = s.top(); 
        s.pop();
        cur->next->prev = cur;
        cur = cur->next;
    }
    cur->next = NULL;
    return head; 
}
```

## 方案三
循环
```cpp
Node* reverse_list3(Node* head){
    Node* pre = NULL, *cur = NULL;
    while (head){
        cur = head->next;
        head->next = pre;
        pre = head;
        head = cur;
    }
    return pre; 
}

biNode* reverse_list3(biNode* head){ 
    biNode *pre = NULL, *cur = NULL;
    while (head){
        cur = head->next;
        head->next = head->prev;
        head->prev = pre;
        pre = head;
        head = cur;
    } 
    return pre; 
}
```