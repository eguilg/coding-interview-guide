# 在二叉树中找到累加和为指定值的最长路径长度

【题目】给定一颗二叉树的头节点head和一个32位整数sum，二叉树节点值类型为整型，求累加和为sum的最长路径长度。路径是指从某个节点向下，每次最多选择一个孩子节点或者不选形成的节点链。

【难度】虎
```c++
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x): val(x), left(NULL), right(NULL) {}
};
```
## 方案一

树中一段路径的累加和，可以由根节点到路径的结束和开始节点的累加和之差表示。即`acc(level)`代表根节点到该路径上第`level`层的累加和，`sum(l1, l2)`代表路径上从`l1`到`l2`层的累加和，则有`sum(l1+1, l2) = acc(l2) - acc(l1)`。

**注意**这个累加和不包括`l1`层的值。所以`sum(1, l) = acc(l) - acc(0)`。

我们可以深度优先遍历每个节点，计算当前路径上的累加和`curSum`，并用map存储路径上出现过的累加和。如果当前的累加和在之前路径上没有出现过，则在map中存入`curSum`和对应的当前`level`，但是如果`curSum`在之前路径有出现，则不更新map中`curSum`对应的`level`，因为对于相同的初始累加和，从更靠近根节点开始可以得到更长的路径。更新map之后，在map中查看是否在之前的路径中有出现过`curSum-sum`的累加和，这样正好差就是`sum`了，所对应的长度就是两个累加和对应的`level`之差。
与当前的`maxLen`对比看是否需要更新。

需要**注意**的是，如果`curSum`正好为`sum`, 即我们需要得到`sum(1, l)`,需要`acc(0)`,所以在初始化map时候要加入一个初始状态`(0, 0)`,即表示累加和为0不用节点就可以得到。

另一个需要**注意**的是，在遍历完当前子树时，需要移除当前层`curSum`的记录，如果之前的层没有出现过`curSum`， 即`curSum`是由当前层第一次得到的，那么就要消除当前层的影响，从map中移除`curSum`,从而可以退回到上一层；如果`curSum`先在之前的level出现的，那么就不用移除。

```cpp
int getSumMaxLength(Node* head, int sum) {
    map<int, int> sumMap;
    sumMap[0] = 0; // 重要
    return preOrder(head, sum, 0, 1, 0, sumMap);
}

int preOrder(Node* head, int sum, int preSum, int level, int maxLen, map<int, int>& sumMap) {
    if (!head){
        return maxLen;
    }
    // 从根节点到当前节点的累加和
    int curSum = head->val + preSum;

    // 如果没有出现过当前的累加和，则在map中存入出现当前累加和的level
    // 注意如果之前出现过curSum的累加和，不会更新level，因为相同的curSum从更早的出发会更长
    if (!sumMap.count(curSum)) {
        sumMap[curSum] = level; 
    }

    // 路径上存在到当前节点累加和为sum的节点, 尝试更新maxLen
    if (sumMap.count(curSum - sum)) {  
        maxLen = max(maxLen, level - sumMap[curSum - sum]);
    }
 
    maxLen = preOrder(head->left, sum, curSum, level + 1, maxLen, sumMap);
    maxLen = preOrder(head->right, sum, curSum, level + 1, maxLen, sumMap);
    
    // 重要：如果curSum在当前level先出现，则移除记录
    // 言下之意如果curSum在上层有先出现，则不应移除
    if (level == sumMap[curSum]) {
        sumMap.erase(curSum);
    }
    return maxLen;
}

```

