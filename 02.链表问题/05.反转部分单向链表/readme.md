# 反转部分单向链表

【题目】反转单向链表中的第from到第to个节点。

【要求】O(N)时间。

【难度】狼
```cpp
struct Node{
    int val;
    Node* next;
    Node(int x): val(x), next(NULL){}
    Node(): val(0), next(NULL){}
};
```
## 方案一

* 先遍历一次得到链表的长度，并且找到第from-1位置的节点```fPre```和第to+1位置的节点```tPos```。
* 反转```fPre```和```tPos```之间的节点，然后正确连接起来。
* 要注意的是如果`from == 1`，即`fPre`为空，那么返回的不再是原来的头节点，而要返回原`tPos`前面的节点；反之则直接返回原来的头即可。
```cpp
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
```