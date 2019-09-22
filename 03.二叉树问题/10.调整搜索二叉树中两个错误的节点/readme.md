# 调整搜索二叉树中两个错误的节点

【题目】一颗树原本是搜索二叉树，但是其中有两个节点交换了位置，使得它不再是BST。找到这两个节点并返回。已知树中每个节点值都不一样。
进阶问题：找到两个节点后，在结构上完全交换两个节点的位置。

【难度】虎 | 神
```c++
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x): val(x), left(NULL), right(NULL) {}
};
```

## 原问题
**对于所有节点值都不同的BST，其中序遍历结果一定是升序的，如果两个节点位置互换了，那么中序遍历就会出现一次或者两次降序。**

如果出现两次降序，第一个错误的节点是第一次降序时较大的，第二个错误节点是第二次降序时较小的。
如果出现一次降序，两个错误节点就是降序的两个节点。

```c++
vector<Node*> getTwoErrNodes(Node* head) {
    vector<Node*> errs(2, nullptr);
    stack<Node*> s;
    Node* pre = nullptr;
    while (!s.empty() || head != nullptr) {
        if (head != nullptr) {
            s.push(head);
            head = head->left;
        } else {
            head = s.top(), s.pop();
            if (pre != nullptr && pre.val > head.val) {
                errs[0] = errs[0] == nullptr ? pre : head;
                errs[1] = head;
            }
            pre = head;
            
            head = head->right;
        }
    }
}
```