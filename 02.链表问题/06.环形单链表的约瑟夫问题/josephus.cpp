# include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};

Node* josephusKill1(Node* head, int m){
    if (!head || head->next == head || m < 1){
        return head;
    }
    Node* last = head;
    int left_num = 1;
    while (last->next != head){
        last = last->next;
        left_num += 1;
    }
    int mm = (m-1) % left_num;
    while (left_num != 1){
        // 找到自杀节点head
        while (mm-- != 0)  {
            last = head;
            head = head->next; 
        }
        last->next = head->next;
        head = last->next;
        left_num--;
        mm = (m-1) % left_num;
    } 
    return last;
}

Node* josephusKill2(Node* head, int m)
{
    if (!head || head->next == head || m < 1){
        return head;
    } 
    int i = 1, cur_num = 1;
    Node* cur = head;
    while (cur->next != head){
        i++;
        cur_num = (cur_num + (m-1)%i) % i + 1;
        cur = cur->next;
    }
    cur = head; 
    while (--cur_num){
        cur = cur->next;
    }
    return cur; 
}


int main(){ 
    Node arr[5]; 
    for (int i = 0; i < 5; ++i)
    {   
        arr[i].val = i+1;
        if (i < 4){
            arr[i].next = &arr[i+1];
        }
        arr[4].next = &arr[0];
    } 
    
    Node* cur2 = josephusKill2(arr, 3);
    Node* cur1 = josephusKill1(arr, 3);
    cout<< cur1->val << " " << cur2->val <<endl;
}