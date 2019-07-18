# include <bits/stdc++.h>

using namespace std;

vector<int> sliding_windwo_maximums(vector<int> &arr, int w)
{
    int n = arr.size();
    if (n-w+1 <= 0 || w < 1)
    {
        return vector<int>();
    }
    vector<int> ans(n - w + 1, 0);
    deque<int> qmax;
    for (int i = 0; i < n; ++i)
    {
        
        while (!qmax.empty() && arr[qmax.back()] <= arr[i])
        {
            qmax.pop_back();
        }
        qmax.push_back(i);

        if (qmax.front() == i - w)
        {
            qmax.pop_front();
        }
        
        if (i >= w-1){
            ans[i-w+1] = arr[qmax.front()];
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {4,3,5,4,3,3,6,7};
    vector<int> ans = sliding_windwo_maximums(arr, 3);
    for (auto a: ans)
    {
        cout<<a<<endl;
    }
}