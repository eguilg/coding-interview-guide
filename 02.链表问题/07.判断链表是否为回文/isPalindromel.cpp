# include<bits/stdc++.h>

using namespace std;
 
struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};

bool isPalindromel1(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* cur = head;
    while (cur){
        s.push(cur);
        cur = cur->next;
    }
    cur = head;
    while (!s.empty() && cur){
        if (s.top()->val != cur->val){
            isP = false;
            break;
        }
        s.pop();
        cur = cur->next;
    }
    return isP;
}

bool isPalindromel2(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* cur = head, *right = head;
    while (right->next && right->next->next){
        right = right->next->next;
        cur = cur->next;
    }
    while(cur->next){
        s.push(cur->next);
        cur = cur->next;
    }
    cur = head;
    while (!s.empty() && cur){
        if (s.top()->val != cur->val){
            isP = false;
            break;
        }
        s.pop();
        cur = cur->next;
    }
    return isP;
} 

Node* reverse_list(Node* head, Node* pre = NULL, Node* end = NULL){
    Node* nxt = NULL;
    while(head != end){
        nxt = head->next;
        head->next = pre;
        pre = head;
        head = nxt;
    } 
    return pre;
}

bool isPalindromel3(Node* head){
    bool isP = true;
    stack<Node*> s;
    Node* mid = head, *right = head;
    while (right->next && right->next->next){
        right = right->next->next;
        mid = mid->next;
    }
    // mid是后半部分的前一个节点，反转后半部分
    Node* rightStart = reverse_list(mid->next, mid);
    // 中间节点的next设为空，用来停止循环遍历
    mid->next = NULL;
    // 左边的头
    Node* left = head;
    // 右边的头
    right = rightStart;
    // 判断是否两头都相同
    while(left){
        if (left->val != right->val){
            isP = false;
            break;
        }
        left = left->next;
        right = right->next;
    }
    // 还原链表的后半部分
    reverse_list(rightStart);
    return isP;
} 

int main(){
    Node arr[5]; 
    int vals[5] = {1,2,3,2,1};
    for (int i = 0; i < 5; ++i)
    {   
        arr[i].val = vals[i];
        if (i < 4){
            arr[i].next = &arr[i+1];
        }
    } 
    cout << isPalindromel3(arr) << endl;
    cout << isPalindromel1(arr) << endl;
    cout << isPalindromel2(arr) << endl;
}