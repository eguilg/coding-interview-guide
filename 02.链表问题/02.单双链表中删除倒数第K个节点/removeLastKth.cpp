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

Node* removeLastKth(Node* head, int K){
    if (!head || K < 1){
        return head;
    }
    Node* cur = head;

    while (cur){
        K--;
        cur = cur->next;
    }
    // 此时的 K 为 K-N
    if (K == 0){ // N - K == 0
        head = head->next;
    }
    // N - K > 0
    if (K < 0){
        cur = head;
        while(++K != 0){ // 再往后走一步就是第N - K个节点时停下
            cur = cur->next;
        }
        cur->next = cur->next->next;
    }
    return head;
}


biNode* removeLastKth(biNode* head, int K){
    if (!head || K < 1){
        return head;
    }
    biNode* cur = head;

    while (cur){
        K--;
        cur = cur->next;
    }
    // 此时的 K 为 K-N
    if (K == 0){ // N - K == 0, 删除头节点
        head = head->next;
        head->prev = NULL;
    }
    // N - K > 0
    if (K < 0){
        cur = head;
        while(++K != 0){ // 再往后走一步就是第N - K个节点时停下
            cur = cur->next;
        }
        cur->next = cur->next->next;
        if(cur->next){ // 需要判断被删除节点的next是否为空，若为空则不能修改其prev
            cur->next->prev = cur;
        }
    }
    return head;
}

Node* removeLastKth2(Node* head, int K){
    if (!head || K < 1){
        return head;
    }
    Node* fast = head, *slow = head;
    while(K && fast){
        fast = fast->next;
        K--;
    }
    
    if (!fast && K == 0){
        head = head->next;
    } else if (K == 0){
        while(fast->next){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
    }
    return head; 
}

int main()
{
    Node arr[10]; 
    for (int i = 0; i < 10; ++i)
    {   
        arr[i].val = i+1;
        if (i != 9){
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

     
    Node* cur = removeLastKth(arr, 10);
    cur = removeLastKth2(cur, 1);
    biNode* curb = removeLastKth(arr_b, 1);
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