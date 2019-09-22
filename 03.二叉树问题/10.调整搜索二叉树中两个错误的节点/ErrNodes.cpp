# include <bits/stdc++.h>
using namespace std;

struct Node
{
    /* data */
    int val;
    Node* left;
    Node* right;

    Node(int x): val(x), left(NULL), right(NULL){}
};

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
            if (pre != nullptr && pre->val > head->val) {
                errs[0] = errs[0] == nullptr ? pre : errs[0];
                errs[1] = head;
            }
            pre = head; 
            
            head = head->right;
        }
    }
    return errs;
}

int main() {
    Node n1(6);
    Node n2(1);
    Node n3(5);
    Node n4(2);
    Node n5(4);
    Node n6(3);

    /*
                n1
        n2               n3
            n4       n5       n6
     */
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    n3.left = &n5;
    n3.right = &n6;

    vector<Node*> errs = getTwoErrNodes(&n1);
    for (auto n : errs) {
        cout << n->val << endl;
    }
}