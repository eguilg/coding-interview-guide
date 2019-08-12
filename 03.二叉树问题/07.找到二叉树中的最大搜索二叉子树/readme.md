# 在二叉树中找到累加和为指定值的最长路径长度

【题目】给定一颗二叉树的头节点head，已知其中所有节点的值都不一样，找到含有节点最多的搜索二叉子树，并返回该子树的头节点。

【要求】O(N)时间空间。

【难度】虎

## 套路：树形DP
* 树形DP套路的前提：题目的解可以通过在**以每一个节点为根的子树**上求解原题目，然后由子树得到的解整合得到。

对于本题，求解目标是**整棵树中的最大二叉搜索子树**，实际上对于每个节点，如果我们分别求得了它左右两颗子树中的最大二叉搜索子树，就可以通过某种整合的方法，得到当前节点的答案。

具体的，如果当前节点为```head```，如果分别求得了其左右子树中最大二叉搜索子树为```max_bst_l```，```max_bst_r```，那么对于```head```节点为根的树来说，它的解就只有三种情况：

1. 解为`head`，即整棵树。出现这种情况的条件比较苛刻，需要整颗`head`为根的树是二叉搜索树，即：
    
    * `max_bst_l == head->left`
    * `max_bst_r == head->right`
    * `head`的值大于其左子树中的最大值，小于其右子树中的最小值。
2. 解为`max_bst_l`。出现这种情况的条件是`max_bst_l`比`max_bst_r`大，而且不满足情况1的条件。
3. 解为`max_bst_r`。出现这种情况的条件是`max_bst_r`比`max_bst_l`大，而且不满足情况1的条件。

可以看到，为了判断情况1的条件，除了左右子树中的最大BST之外，我们还需要同时求得左右子树中的最大最小值，来判断`head`树是否满足BST的条件。

那么对于每棵子树，我们需要求的信息有：

* 该树中最大搜索二叉子树的**根**及其**大小**。
* 该子树的最大、最小值

我们可以用一个结构体来记录：
```cpp
struct Info {
    Node* maxBSTHead; // 最大搜索树的根节点
    int maxBSTSize; // 最大搜索树的大小
    int min_val; // 整棵树的最小值
    int max_val; // 整棵树的最大值

    Info(Node* maxBSTHead, int maxBSTSize, int minv, int maxv):
    maxBSTHead(maxBSTHead), maxBSTSize(maxBSTSize), min_val(minv), max_val(maxv){}
};
```

整个的遍历过程由于是先求左右子树，再在根节点进行整合，所以是二叉树的后序遍历：

```cpp
Info postOrder(Node* head) {
    if (!head) {
        return Info(NULL, 0, INT_MAX, INT_MIN);
    }

    Info l_info = postOrder(head->left);
    Info r_info = postOrder(head->right);

    // 整合信息
    int minv = min(head->val, min(l_info.min_val, r_info.min_val));
    int maxv = max(head->val, max(l_info.max_val, r_info.max_val));

    int maxBSTSize = max(l_info.maxBSTSize, r_info.maxBSTSize);
    Node* maxBSTHead = l_info.maxBSTSize > r_info.maxBSTSize ? l_info.maxBSTHead : r_info.maxBSTHead;

    // 当前整棵树是BST 需要满足左子树最大值小于当前head，右子树最小值大于当前head
    if (l_info.maxBSTHead == head->left && r_info.maxBSTHead == head->right 
        && l_info.max_val < head->val && r_info.min_val > head->val) {
            maxBSTSize = 1 + l_info.maxBSTSize + r_info.maxBSTSize;
            maxBSTHead = head;
        }
    return Info(maxBSTHead, maxBSTSize, minv, maxv); 
}
```
最后主函数调用即可：
```cpp
Node* getMaxBST(Node* head) {
    return postOrder(head).maxBSTHead;
}
```

## 总结
树形DP四步：

1. 在**以任意节点为根的子树**X上，从X左子树、右子树和X整棵树的角度，分析原问题答案的可能性。
2. 根据第一步分析的可能性，列出需要从每棵子树获取的信息。
3. 合并上一步所需的信息，统一左右子树获取的信息结构。
4. 设计递归函数，包括初始状态，得到左右子树信息后如何根据信息判断不同的情况，然后做信息整合。