# 构造数组的MaxTree
【题目】一个数组的MaxTree定义：
1. 数组必须**没有重复**元素。
2. MaxTree是一颗二叉树，数组每一个值对应一个节点。
3. 包括MaxTree树在内的每一棵子树，其最大的节点都是其根节点。

【要求】O(n)时间空间。

【难度】鬼

## 方案一
构建规则：
* 每一个数的父节点是它左右两边第一个比它大的数中，较小的那个。
* 如果一个数左右都没有比它大的树，则为整棵树的根节点。

这样得到的树一定是二叉树，因为数组中任何一个数字，在其一侧只会有一个节点是它的孩子。
证明：

若一侧存在两个孩子，如

```...a...k1...k2...```

若k1、k2都是a的孩子，那么有```a > k1, a > k2 且 k1 != k2```，但是若```k1 < k2```，```k1```应该认```k2```为父亲，反之亦反。所以```a```的右边孩子应该是```k1```和```k2```中较大的那个。

如何快速找到数组中每个数左右两边第一个比它大的数？

还是单调栈。例如找每个数左边第一个比它大的数，用单调递减栈，保持栈顶最小。遇到新来的不断出栈，直到栈空或栈顶比新的数大。

能找到每个节点的父节点，就可以通过map来构建树了。

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
    TreeNode(): val(0), left(NULL), right(NULL){}
};

TreeNode* getMaxTree(vector<int> & arr){

    stack<int> s;
    vector<int> parents(arr.size(), -1); // 存放每个数的父亲的索引，-1表示根节点

    //找每个数左边比它大的第一个
    for(int i = 0; i < arr.size(); ++i)
    {
        while (!s.empty() && arr[s.top()] <= arr[i])
        {
            s.pop();
        }
        if (!s.empty()){
            parents[i] = s.top();
        }
        s.push(i);
    }
    // 清空栈
    s = stack<int>();
    // 存根节点的索引
    int root_idx = -1;
    // 找每个数右边比它大的第一个，并且与左边比他大的第一个比较，去最小的
    for(int i = arr.size()-1; i >= 0; --i)
    {
        while (!s.empty() && arr[s.top()] <= arr[i])
        {
            s.pop();
        }
        if (!s.empty() && (parents[i] == -1 || arr[parents[i]] > arr[s.top()])){
            parents[i] = s.top();
        }
        if (parents[i] == -1)
        {
            root_idx = i;
        }
        s.push(i);
    }

    // 初始化nodes数组
    vector<TreeNode*> nodes(arr.size(), NULL);
    for (int i = 0; i < arr.size(); ++i)
    {
        nodes[i] = new TreeNode();
    }

    // 让每个node与其父亲连接
    TreeNode *root = NULL;
    for (int i = 0; i < arr.size(); ++i)
    {
        nodes[i]->val = arr[i];
        if (parents[i] == -1){
            root = nodes[i];
        }else if (parents[i] > i)
        {
            nodes[parents[i]]->left = nodes[i];
        } else {
            nodes[parents[i]]->right = nodes[i];
        }
    } 
    return root;
}
```

