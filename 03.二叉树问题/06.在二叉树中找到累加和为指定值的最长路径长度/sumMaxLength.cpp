# include<bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x): val(x), left(NULL), right(NULL) {}
};



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

int getSumMaxLength(Node* head, int sum) {
    map<int, int> sumMap;
    sumMap[0] = 0; // 重要
    return preOrder(head, sum, 0, 1, 0, sumMap);
}

int main() {
    Node n1(1);
    Node n2(4);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);

    /*
                1
        4               3
            4       5       6
     */
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    n3.left = &n5;
    n3.right = &n6;

    cout << getSumMaxLength(&n1, 9) << endl;
}