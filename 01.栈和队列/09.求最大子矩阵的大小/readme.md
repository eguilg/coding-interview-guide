# 求最大子矩阵的大小
【题目】给定一个整形矩阵，只有0和1两种值，求只有1组成的最大子矩阵的大小。

【要求】O(MN)时间。

【难度】鬼

## 方案一
遍历每一行，统计当前行每个位置上方连续的1的数量，这样对于每一行可以得到一个直方图数组```height```，
然后用单调栈求这个直方图里的最大面积，即为以当前行为底边的最大全1矩形的面积。最后取每一行中最大面积的最大值为结果即可。

具体的，在统计第```i```行第```j```位置的height时:

```height[j] = mat[i][j] == 0 ? 0 : height[j]+1```

```cpp
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
```
对于此行，求以该行为底边的最大矩阵的问题就转化成了求直方图内最大矩形的问题：

遍历```hist```，当前位置为```hist[i]```，维护一个单调递增栈```maxS```:

1. 如果```maxS```非空，且```栈顶 >= hist[i]```，取其栈顶```j```弹出，```hist[j]```作为此次计算的矩形的高度。
2. 如果```maxS```非空，取其栈顶```k```，若```maxS```为空，则令```k=-1```。这里```k```为最近一个比```hist[j]```小的位置，我们要计算的矩形是```[k+1, i-1]```范围内的。
3. 更新最大矩形面积，回到1直到```栈顶 < hist[i]```或者栈空。
4. ```i```入栈。

步骤3中，计算新的最大矩形面积：

```max_area = max(max_area, hist[j] * (i - k - 1))```

就是这样:
```cpp
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
            ans = max(ans, hist[j] * (i - k -1));
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
```

时间复杂度：对于每一行，实际上是一个求直方图最大矩形问题，每个位置最多入栈出栈一次，就是O(N)，一共有M行，所以最后是O(MN)。






