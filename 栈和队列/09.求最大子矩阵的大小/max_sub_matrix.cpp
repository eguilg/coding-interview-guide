# include <bits/stdc++.h>

using namespace std;

int max_rect_in_hist(vector<int>& hist)
{
    int ans = 0;
    stack<int> maxS;
    for (int i = 0; i < hist.size(); ++i)
    {
        while(!maxS.empty() && hist[maxS.top()] >= hist[i])
        {
            int j = maxS.top();
            maxS.pop();
            // k为上一个比hist[j]小的位置，即矩形的开始位置前一个位置
            int k = maxS.empty()? -1 : maxS.top();
            ans = max(ans, hist[j] * (i - k - 1));
        }
        maxS.push(i);
    }

    while(!maxS.empty())
    {
        int j = maxS.top();
        maxS.pop();
        int k = maxS.empty()? -1 : maxS.top();
        ans = max(ans, int(hist[j] * (hist.size() - k -1)));
    }
    return ans;
}

int max_sub_matrix(vector<vector<int>>& mat){
    int m = mat.size();
    if (m == 0){
        return 0;
    }
    int n = mat[0].size();
    if (n == 0){
        return 0;
    }

    vector<int> hist(n, 0);
    int ans = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            hist[j] = mat[i][j] == 0 ? 0 : hist[j]+1;
        }
        ans = max(ans, max_rect_in_hist(hist));
        for(auto h : hist)
        {
            cout << h << " ";
        }
        cout << endl;
    } 
    return ans;
}



int main(){
    vector<int>hist = {3,2,3,0};
    cout << max_rect_in_hist(hist)<<endl;

    vector<vector<int>> mat = {
        {0,1,1,1},
        {1,1,1,1},
        {1,1,1,0},
    };
    cout<< max_sub_matrix(mat)<<endl;
}