# include <bits/stdc++.h>
# include <limits>
using namespace std;

struct Node
{
    /* data */
    int val;
    Node* left;
    Node* right;

    Node(int x): val(x), left(NULL), right(NULL){}
};


/**************************************************************
 * 方法一   O(n^2)                                                   *
 **************************************************************/
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

// 必须以h节点为根节点时候，n节点为根的子树贡献的拓扑大小
int maxTopoFromHead(Node* h, Node* n) {
    if (h && n && isBSTNode(h, n, n->val)) { // 从h到n的路径符合bst规则，n节点可以加入到拓扑中
        return 1 + maxTopoFromHead(h, n->left) + maxTopoFromHead(h, n->right); // 返回n节点为根的最大拓扑数量
    }
    return 0;
}

// n^2的方法。对于每个节点求从该节点开始的最大bst拓扑结构，取所有中的最大的。
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


/**************************************************************
 * 方法二  O(n)                                                *
 **************************************************************/


struct Record { //拓扑贡献记录
    int l; // 节点的左子树对该节点贡献的拓扑大小
    int r; // 节点的右子树对该节点贡献的拓扑大小
    Record(int left, int right): l(left), r(right) {}
    Record(): l(0), r(0) {}
};

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

// 返回head为根的树中最大bst拓扑大小
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

int bstTopoSize2(Node* head) {
    map<Node*, Record> m;
    return postOrder(head, m);
}


int main() {
    Node n1(5);
    Node n2(3);
    Node n3(4);
    Node n4(6);
    Node n5(8);
    Node n6(7);

    /*
                5
        3               4
            6       8       7
     */
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    n3.left = &n5;
    n3.right = &n6;
    cout << bstTopoSize1(&n1) << endl;
    cout << bstTopoSize2(&n1) << endl;

}