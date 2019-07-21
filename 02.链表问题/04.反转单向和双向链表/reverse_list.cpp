# include<bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};

struct biNode{
    int val;
    biNode* next;
    biNode* prev;
    biNode(int x): val(x), next(NULL), prev(NULL){}
    biNode(): val(0), next(NULL), prev(NULL){}
};

Node* reverse_list1(Node* head)
{
    if (!head || !head->next){
        return head;
    }
    Node* newTail = head->next;
    Node* newHead = reverse_list1(head->next);
    newTail->next = head;
    head->next = NULL;
    return newHead;
}

biNode* reverse_list1(biNode* head)
{
    if (!head || !head->next){
        return head;
    }
    biNode* newTail = head->next;
    biNode* newHead = reverse_list1(head->next);
    newTail->next = head;
    head->prev = newTail;
    head->next = NULL;
    return newHead;
}

Node* reverse_list2(Node* head){
    if (!head || !head->next){
        return head;
    }
    stack<Node*> s;
    while (head){
        s.push(head);
        head = head->next;
    }
    head = s.top();
    Node *cur = head;
    s.pop();
    while (!s.empty()){
        cur->next = s.top();
        s.pop();
        cur = cur->next;
    }
    cur->next = NULL;
    return head; 
}

biNode* reverse_list2(biNode* head){
    if (!head || !head->next){
        return head;
    }
    stack<biNode*> s;
    while (head){
        s.push(head);
        head = head->next;
    }
    head = s.top(); 
    s.pop();
    head->prev = NULL;
    biNode *cur = head; 
    while (!s.empty()){
        cur->next = s.top(); 
        s.pop();
        cur->next->prev = cur;
        cur = cur->next;
    }
    cur->next = NULL;
    return head; 
}


Node* reverse_list3(Node* head){
    Node* pre = NULL, *nxt = NULL;
    while (head){
        nxt = head->next;
        head->next = pre;
        pre = head;
        head = nxt;
    }
    return pre; 
}

biNode* reverse_list3(biNode* head){ 
    biNode *pre = NULL, *nxt = NULL;
    while (head){
        nxt = head->next;
        head->next = head->prev;
        head->prev = pre;
        pre = head;
        head = nxt;
    } 
    return pre; 
}


int main()
{
    Node arr[10]; 
    for (int i = 0; i < 10; ++i)
    {   
        arr[i].val = i+1;
        if (i < 9){
            arr[i].next = &arr[i+1];
        }
    } 
    biNode arr_b[10]; 
    for (int i = 0; i < 10; ++i)
    {   
        arr_b[i].val = i+1;
        if (i != 9){
            arr_b[i].next = &arr_b[i+1];
        }
        if (i != 0){
            arr_b[i].prev = &arr_b[i-1];
        }
    }

    Node* cur = reverse_list3(arr);
    biNode* curb = reverse_list3(arr_b);
    while (cur){
        cout << cur->val<< " ";
        cur = cur->next;
    }
    cout << endl;
    while (curb){
        cout << curb->val<<" ";
        curb = curb->next;
    }
    cout << endl;
}