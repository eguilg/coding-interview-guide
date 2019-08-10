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
前序遍历的非递归方法用栈保存接下来要访问的节点。先将根节点入栈，进入循环，每次取栈顶节点打印，然后将其右孩子(如果存在)入栈，再将其左孩子(如果存在)入栈，注意入栈的顺序是和打印的顺序相反的，所以想要左->右打印就得先右后左入栈。
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
中序遍历一直向左遍历，同时将路径上的节点都入栈，直到最左端，然后出栈、打印每个节点，打印之后将该节点的右孩子入栈，然后进入右边子树重复上述过程。
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
    cout << head->val << " ";
}
```

### 非递归方法
后续遍历就有些复杂了，因为是 左->右->中 的顺序，但是从左到右又需要经过中，所以在需要有一个变量seen来记录最近一次访问的节点。

每次取出当前栈顶的节点时，有三种情况：

* [unseen, cur, unseen], 其中左右的unseen代表左右孩子都存在且都没被访问过，这个时候左中右三个节点都没被访问，那么先要进入左边子树，所以左孩子入栈。
* [seen, cur, unseen], 左孩子seen代表上次访问的是左孩子或者左孩子为空，这时候左子树为空或者已经访问过了，需要进入右边树，所以右孩子入栈。
* [seen, cur, seen], 右孩子是上一次访问的节点，那就意味着左边肯定也被访问过了，按照后序的顺序，这时可以访问当前节点了，打印cur并出栈即可。
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