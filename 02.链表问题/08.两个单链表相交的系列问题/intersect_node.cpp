# include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};

Node* getLoopNode(Node* head)
{
    if (!head || !head->next){
        return head;
    } 
    Node* slow = head->next;
    Node* fast = head->next->next;
    while (fast && fast->next && fast != slow){
        fast = fast->next->next;
        slow = slow->next;
    } 
    if (fast != slow){
        return NULL;
    }
    fast = head;
    while (fast != slow){
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

Node* noLoopIntersect(Node* head1, Node* head2, Node* co_tail=NULL){
    if (!head1 || !head2){
        return NULL;
    }
    int len1 = 1, len2 = 1;
    Node* cur1 = head1;
    Node* cur2 = head2;
    while(cur1->next != co_tail){
        cur1 = cur1->next;
        len1++;
    }
    while(cur2->next != co_tail){
        cur2 = cur2->next;
        len2++;
    }
    if (cur1 != cur2){
        return co_tail;
    }
    if (len1 > len2){
        for (int i = 0; i < len1 - len2; ++i){
            head1 = head1->next;
        }
    }  else {
        for (int i = 0; i < len2 - len1; ++i){
            head2 = head2->next;
        }
    } 
    while (head1 != head2){
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1;
}

Node* loopIntersect(Node* head1, Node* loop1, Node* head2, Node* loop2){
    // 入环点相同，则问题变为求入环之前的第一个交点，跟问题二一致
    if (loop1 == loop2){
        return noLoopIntersect(head1, head2, loop1);
    } 
    // 入环点不同，则看从loop1能否到达loop2
    Node* cur = loop1->next;
    while (cur != loop1 && cur != loop2){
        cur = cur->next;
    }
    if (cur == loop1){ //回到了loop1,说明没相交
        return NULL;
    } else {
        return loop1;   // 找到了loop2，说明相交了，返回loop1 loop2均可
    } 
}

Node* getIntersectNode(Node* head1, Node* head2){
    Node* loop1 = getLoopNode(head1);
    Node* loop2 = getLoopNode(head2);

    if (!loop1 && !loop2){
        return noLoopIntersect(head1, head2);
    } else if (loop1 && loop2){
        return loopIntersect(head1, loop1, head2, loop2);
    }  
    return NULL; 
}