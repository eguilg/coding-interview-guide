# include <bits/stdc++.h>
# include <limits>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x): val(x), left(NULL), right(NULL){}
};

struct Info {
    Node* maxBSTHead; // 最大搜索树的根节点
    int maxBSTSize; // 最大搜索树的大小
    int min_val; // 整棵树的最小值
    int max_val; // 整棵树的最大值

    Info(Node* maxBSTHead, int maxBSTSize, int minv, int maxv):
    maxBSTHead(maxBSTHead), maxBSTSize(maxBSTSize), min_val(minv), max_val(maxv){}
};

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

Node* getMaxBST(Node* head) {
    return postOrder(head).maxBSTHead;
}

int main() {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);

    /*
                1
        2               3
            4       5       6
     */
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    n3.left = &n5;
    n3.right = &n6;
    cout << getMaxBST(&n1)->val << endl;

}