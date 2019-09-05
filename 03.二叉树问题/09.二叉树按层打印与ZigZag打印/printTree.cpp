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

void printByLevel(Node* root) {
    if (root == NULL) {
        return;
    }
    list<Node*> q;
    int level = 1;
    q.push_back(root);
    Node* cur = NULL;
    while (!q.empty()) {
        cout << "Level " << level << " : ";
        size_t size = q.size();
        while(size--) {
            cur = q.front();
            q.pop_front();
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
    cout << "by level:" << endl;
    printByLevel(&n1);
    cout << "zigzag:" << endl;
    printZigZag(&n1);

}