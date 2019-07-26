# include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};


Node* reverseKNodes1(Node* head, int k){
    if (k < 2){
        return head;
    }
    stack<Node*> s;
    Node* newHead = head;
    Node* pre = NULL, * cur = head, *nxt = NULL;
    while(cur != NULL){
        nxt = cur->next;
        s.push(cur);
        if (s.size() == k){
            while (!s.empty()){
                if (!pre){
                    newHead = s.top();
                    pre = newHead;
                } else {
                    pre->next = s.top();
                    pre = pre->next;
                    pre->next = nxt;
                }
                s.pop();
            }
        }
        cur = nxt; 
    }
    return newHead;
}

/*
反转从[head, end)区间内的链表节点，并将反转后的头尾与pre、end连接 
返回新的头
 */
Node* reverse_part_list(Node* head, Node* pre=NULL, Node* end=NULL){
    Node* nxt = NULL;
    while(head != end){
        nxt = head->next;
        head->next = pre;
        pre = head;
        head = nxt;
    }
    return pre;
}

Node* reverseKNodes2(Node* head, int k){
    if (k < 2){
        return head;
    } 
    Node* cur = head, *pre = NULL, *nxt = head;
    int count = 0;
    while (cur){
         nxt = cur->next;
         if (count == k){
             if (pre){
                 pre->next = reverse_part_list(pre->next, NULL, nxt);
             } else{
                 pre = head;
                 head = reverse_part_list(head, NULL, nxt);
                 pre->next = nxt;
             }
         }
         count++;
         cur = nxt;
    }
    return head;
}

int main(){
    Node arr[8]; 
    int vals[8] = {1,2,3,4,5,6,7,8};
    for (int i = 0; i < 8; ++i)
    {   
        arr[i].val = vals[i];
        if (i < 7){
            arr[i].next = &arr[i+1];
        }
    }  
    Node* cur = reverseKNodes2(arr, 3);
    while (cur){
        cout << cur->val<< " ";
        cur = cur->next;
    }
}