# include<bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};


Node* reverse_part_list(Node* head, int from, int to){
    int len = 0;
    Node* cur = head, *fPre = NULL, *tPos = NULL;
    while (cur) {
        // 找到from前一个和to后一个
        ++len;
        fPre = len == from - 1 ? cur : fPre;
        tPos = len == to + 1 ? cur : tPos;
        cur = cur->next;
    } 
    // 如果from to 不在链表长度范围内，不用调整
    if (from > to || from < 1 || to > len) {
        return head;
    } 
    Node *pre = fPre ? fPre->next : head; //from 节点
    cur = pre->next;
    pre->next = tPos; // from反转后在tPos前面
    Node* nxt = NULL;
    while (cur != tPos) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    //from 不是头节点
    if (fPre){
        fPre->next = pre;
        return head;
    }
    //from 是头节点，返回pre
    return pre; 
}

int main(){

    Node arr[10]; 
    for (int i = 0; i < 10; ++i)
    {   
        arr[i].val = i+1;
        if (i < 9){
            arr[i].next = &arr[i+1];
        }
    } 
    Node* cur = reverse_part_list(arr, 2, 6);
    while (cur){
        cout << cur->val<< " ";
        cur = cur->next;
    }
}