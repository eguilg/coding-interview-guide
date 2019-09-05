# 二叉树按层打印与ZigZag打印

【题目】给定一颗二叉树，分别实现按层打印和ZigZag打印。

【难度】虎
```c++
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x): val(x), left(NULL), right(NULL) {}
};
```

## 按层打印
``` cpp
void printByLevel(Node* root) {
    if (root == NULL) {
        return;
    }
    list<Node*> q;
    int level = 1;
    q.push_back(q);
    Node* cur = NULL;
    while (!q.empty()) {
        cout << "Level " << level << " : ";
        size_t size = q.size();
        while(size--) {
            cur = q.pop_front();
            if (cur->left) {
                q.push_back(cur->left);
            }
            if (cur->right) {
                q.push_back(cur->right);
            }
            cout << cur->val;
            if (size) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
        level ++;
    } 
}
```

## ZigZag打印
```cpp
void printZigZag(Node* root) {
    if (root == NULL) {
        return;
    }
    list<Node*> q;
    int level = 1;
    q.push_back(root);
    Node* cur = NULL;
    bool isL2R = true;
    while (!q.empty()) {
        isL2R = level % 2 == 1;
        cout << "Level " << level << " from " << (isL2R ? "left to right: " : "right to left: ");
        size_t size = q.size();
        while (size--)
        {
            if (isL2R) {
                cur = q.front();
                q.pop_front();
                if (cur->left) {
                    q.push_back(cur->left);
                } 
                if (cur->right) {
                    q.push_back(cur->right);
                }
            } else {
                cur = q.back();
                q.pop_back();
                if (cur->right) {
                    q.push_front(cur->right);
                }
                if (cur->left) {
                    q.push_front(cur->left);
                }
            }
            cout << cur->val;
            if (size) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
        level ++;
    } 
}
```