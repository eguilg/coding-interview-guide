# 二叉树前中后序遍历

【题目】二叉树前中后序遍历。

【要求】递归非递归。

【难度】鬼

## 前序遍历

### 递归方法

```c++
void preOrderRecur(Node* head){
    if (!head) {
        return;
    }
    cout << head->val << " ";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}
```

### 非递归方法

```c++
void preOrder(Node* head) {
    if (!head) {
        return;
    }
    stack<Node*> s;
    s.push(head);
    while(!s.empty()) {
        head = s.top(); s.pop();
        cout << head->val;
        if (head->right) {
            s.push(head->right);
        }
        if (head->left) {
            s.push(head->left);
        }
    }
    cout << endl;
}
```

## 中序遍历

### 递归方法

```c++
void InorderRecur(Node* head){
    if (!head) {
        return;
    }
    InorderRecur(head->left);
    cout << head->val << " ";
    InorderRecur(head->right);
}
```

### 非递归方法

```c++
void inOrder(Node* head) {
    if (!head) {
        return;
    }
    stack<Node*> s; 
    while (!s.empty() || head) {
        if (head) {
            s.push(head);
            head = head->left;
        } else {
            head = s.top(); s.pop();
            cout << head->val << " ";
            head = head->right;
        }
    }
    cout << endl;
}
```

## 后序遍历

### 递归方法

```c++
void posOrderRecur(Node* head) {
    if (!head) {
        return;
    }
    posOrderRecur(head->left);
    posOrderRecur(head->right);
    cout << head->val << endl;
}
```

### 非递归方法
```c++
void posOrder(Node* head) {
    if (!head) {
        return;
    }
    stack<Node*> s;
    s.push(head);
    Node* seen = head;

    while (!s.empty()) {
        head = s.top();
        if (head->left && seen != head->left && seen != head->right) { // 左右都没见过，而且有左边孩子
            s.push(head->left); 
        } else if (head->right && seen != head->right) { // 左边刚见过或者没有左边孩子， 同时右边孩子存在且没见过
            s.push(head->right);
        } else {  // 左右都遍历过了或者没有，才能遍历当前节点
            cout << head->val << " ";
            s.pop();
            seen = head;
        }
    }
    cout << endl;
}
```