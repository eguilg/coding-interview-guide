# include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
    TreeNode(): val(0), left(NULL), right(NULL){}
};

TreeNode* getMaxTree(vector<int> & arr){

    stack<int> s;
    vector<int> parents(arr.size(), -1); // 存放每个数的父亲的索引，-1表示根节点

    //找每个数左边比它大的第一个
    for(int i = 0; i < arr.size(); ++i)
    {
        while (!s.empty() && arr[s.top()] <= arr[i])
        {
            s.pop();
        }
        if (!s.empty()){
            parents[i] = s.top();
        }
        s.push(i);
    }
    // 清空栈
    s = stack<int>(); 
    // 找每个数右边比它大的第一个，并且与左边比他大的第一个比较，去最小的
    for(int i = arr.size()-1; i >= 0; --i)
    {
        while (!s.empty() && arr[s.top()] <= arr[i])
        {
            s.pop();
        }
        if (!s.empty() && (parents[i] == -1 || arr[parents[i]] > arr[s.top()])){
            parents[i] = s.top();
        } 
        s.push(i);
    }

    // 初始化nodes数组
    vector<TreeNode*> nodes(arr.size(), NULL);
    for (int i = 0; i < arr.size(); ++i)
    {
        nodes[i] = new TreeNode();
    }

    // 让每个node与其父亲连接
    TreeNode *root = NULL;
    for (int i = 0; i < arr.size(); ++i)
    {
        nodes[i]->val = arr[i];
        if (parents[i] == -1){
            root = nodes[i];
        }else if (parents[i] > i)
        {
            nodes[parents[i]]->left = nodes[i];
        } else {
            nodes[parents[i]]->right = nodes[i];
        }
    } 
    return root;
}


void print_tree(TreeNode* root)
{
    queue<TreeNode*> nodes;
    nodes.push(root);
    TreeNode* cur = NULL;
    while (!nodes.empty())
    {
        int k = nodes.size();
        for (; k > 0; k--)
        {
            cur = nodes.front();
            if (cur)
            {
                nodes.push(cur->left);
                nodes.push(cur->right);
                cout<<cur->val;
            }else {
                cout << " ";
            }
            if (k != 1){
                cout << " ";
            }
            nodes.pop();
        }
        cout << endl;
    }
}

int main(){
    vector<int> arr = {3,4,5,8,1,2,7,9};
    TreeNode* root = getMaxTree(arr);
    print_tree(root);

}