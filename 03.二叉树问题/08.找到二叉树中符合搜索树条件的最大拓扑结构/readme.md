# 找到二叉树中符合搜索树条件的最大拓扑结构

【题目】给定一颗二叉树的头节点head，已知其中所有节点的值都不一样，返回其中最大的且符合搜索二叉树条件的最大拓扑结构的大小。

【要求】O(N)时间空间。

【难度】鬼

## 方案一
对于每一个节点，求以该节点为根的符合搜索树条件的最大拓扑结构。具体的，相当于有两层遍历，外层遍历整颗二叉树，目的是得到以每个节点`h`为根的符合条件的最大拓扑的大小。外层遍历的递归函数：
```cpp
int bstTopoSize1(Node* head) {
    if (!head) {
        return 0;
    }
    // 对每个节点求以之为根的最大拓扑大小
    int max_size = maxTopoFromHead(head, head);
    max_size = max(bstTopoSize1(head->left), max_size);
    max_size = max(bstTopoSize1(head->right), max_size);

    return max_size;
}
```
内层遍历从外层的当前节点`h`开始遍历`h`为根的子树，对于遍历到的每个节点`n`，按照bst的搜索方式在`h`子树中查找`n->val`，如果能找到`n`，说明`n`可以加入当前的拓扑结构，并继续遍历。

内层遍历：
```cpp
// 必须以h节点为根节点时候，n节点为根的子树贡献的拓扑大小
int maxTopoFromHead(Node* h, Node* n) {
    if (h && n && isBSTNode(h, n, n->val)) { // 从h到n的路径符合bst规则，n节点可以加入到拓扑中
        return 1 + maxTopoFromHead(h, n->left) + maxTopoFromHead(h, n->right); // 返回n节点为根的最大拓扑数量
    }
    return 0;
}
```

内层遍历中对每个节点判断是否能纳入`h`为根的拓扑中，即从`h`出发查找`value`，返回是否能找到`n`节点：
```cpp
// 从head节点按照bst的路径查找value， 看是否能走到n节点
bool isBSTNode(Node* h, Node* n, int value) {
    if (!h) { // 没找到n节点就走到了叶子
        return false;
    }
    if (h == n) { // 找到了n节点
        return true;
    }
    // 按照bst搜索value的规则接着向下找n节点
    return isBSTNode(h->val > value ? h->left : h->right, n, value);
}
```
该方嵌套了两层二叉树遍历，内层遍历的操作是O(logN)，两层遍历O(N^2)，最终复杂度O(N^2)。重复的计算在于对于每个子节点计算了多次最大拓扑。

## 方案二
方案一中对于每个子节点重复计算了多次最大拓扑，但是如果每个节点只算一次最大拓扑行不行呢？比如对于某个子节点`h`，已经得到了`h->left`和`h->right`两颗子树中的最大拓扑，是否可以直接得到`h`子树中最大拓扑呢？我们想从左右子树中各自最大拓扑得到父亲的最大拓扑，所以实际上这还是一个树形DP问题，按照套路来。

首先分析以`h`为根的子树，这棵树中的最大拓扑实际上来自三种情况：
1. `h`为根的最大拓扑。
2. 左子树中的最大拓扑。
3. 右子树中的最大拓扑。

应该如何判断这三种情况呢？我们默认已经得到了左右子树中的最大拓扑结构大小，只要计算`h`为根的最大拓扑大小，然后取三者中的最大即可。实现上来说是一个后续遍历：

想要求`h`为根的最大二叉搜索拓扑大小，我们需要从两颗子树中知道，它们能为`h`节点提贡献大满足条件的拓扑结构，这里我们默认已经得到了`h->left`和`h->right`为根的两颗子树中，每个节点对其父亲贡献的拓扑大小，实现上可以用map存放，即`m[node] = Record(l, r)`，l,r分别代表其左右孩子为它贡献的拓扑大小。

用这样的结构体来表示每个节点的左右子树对其的贡献：
```cpp
struct Record { //拓扑贡献记录
    int l; // 节点的左子树对该节点贡献的拓扑大小
    int r; // 节点的右子树对该节点贡献的拓扑大小
    Record(int left, int right): l(left), r(right) {}
    Record(): l(0), r(0) {}
};
```

整个过程一个后序遍历，先得到左右子树中各自的最大拓扑结构，同时存好其中每个节点的拓扑记录，然后根据已有记录，对当前节点左右孩子为根的拓扑进行剪裁，计算得到当前节点的拓扑记录并存入map中：
```cpp
int postOrder(Node* head, map<Node*, Record>& m) {
    if (!head) {
        return 0;
    }

    int l_size = postOrder(head->left, m);
    int r_size = postOrder(head->right, m);

    // 根据左右子树得到的信息更新记录
    int l_contrib = getTopoContrib(head, m, true);
    int r_contrib = getTopoContrib(head, m, false);

    m[head] = Record(l_contrib, r_contrib);
    return max(l_contrib + r_contrib + 1, max(l_size, r_size)); 
}
```
但是我们并*不能*通过`m[h].l = (m[h->left].l + m[h->left].r + 1)`和`m[h].r = (m[h->right].l + m[h->right].r + 1)`这样来计算左右孩子对`h`的贡献，因为`h->left`为根的最大拓扑可能并不能完全贡献于`h`，需要剪裁`h->left`为根的最大拓扑，只留下其中小于`h->val`的部分，对于`h->right`也同理，只留下其中大于`h->val`的部分，具体的做法是遍历`h`左子树的右边界，直到大于`h->val`的位置剪裁，遍历右子树的左边界，直到小于`h->val`的时候剪裁：

```cpp
int getTopoContrib(Node* head, map<Node*, Record>& m, bool isLeft) {
    Node* child = isLeft ? head->left : head->right;
    Node* cur = child;
    
    int minus = 0;
    Record cur_rc;
    // 判断是否左子树上界、右子树下界与head不符合bst
    while (cur && ((isLeft && cur->val < head->val) || (!isLeft && cur->val > head->val))) {
        cur_rc = m[cur];
        minus = isLeft ? cur_rc.r : cur_rc.l;
        cur = isLeft ? cur->right : cur->left;
        if (minus == 0) {
            break;
        }
    }
    // 循环结束时的cur为空或者是第一个不符合bst条件的边界节点
    // 同时minus为cur为根的子树对其父的贡献 

    // head的左/右孩子为空或者直接不符合bst，不贡献
    if (cur == child) {
        return 0;
    } 
    Record child_rc = m[child]; 
    return child_rc.l + child_rc.r + 1 - minus;
}
```
最后外层的调用函数：
```cpp
int bstTopoSize2(Node* head) {
    map<Node*, Record> m;
    return postOrder(head, m);
}
```
方案二外层是一个后序遍历，复杂度O(N)，后序遍历中的操作实际上是分别遍历左右子树的右边界、左边界，复杂度为O(logN),所以总的复杂度为O(N)。

## 总结
很巧妙的方法，真正的树形DP。
