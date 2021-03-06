# 生成窗口最大值数组
【题目】整形数组arr，大小为w的滑窗从数组的左边滑到右边，窗口每次右滑一个位置。窗口最大值指某个位置的窗口内的最大值，则若数组长为n，窗口大小w,一共产生n-w+1个窗口最大值。求所有的窗口最大值。

【要求】O(n)

【难度】虎
## 方案一
遍历arr的过程中不断遍历窗口寻找最大值，O(w×n)不得行。
## 方案二
在窗口向右滑动的过程中，每前进一个位置都有一个元素滑出窗口，一个元素进入窗口，这时窗口里比新进入的元素小的在以后都不会成为最大值了。

所以我们需要一个数据结构来存储以后可能成为最大值的元素。每次新来一个元素，不断和待选元素里的最小值比较，若新元素大于当前最小值，则将最小值移除，直到待选为空或者新的元素是最小值，也要方便得到待选元素中的最大值作为答案，同时要方便地移除过期(滑出窗口的)元素。

这里我们需要使用双端单调队列，让这个双端队列从头到尾递减，每次比较新元素与队尾，如果小于队尾，直接加入队尾，反之不断弹出队尾，直到新元素小于队尾或者队列为空。同时每次从队列头部得到最大值，或者移除过期元素。

用```qmax```表示双端单调队列，当前遍历到```arr[i]```那么具体的

放入规则：
1. ```qmax```为空，直接将下标```i```加入```qmax```尾部。
2. ```qmax```不为空，得到当前队列尾```j```。
3. ```arr[j] > arr[i]```，直接将```i```加入队尾。
4. ```arr[j] <= arr[i]```, 从队尾弹出```j```，回到1重复。

弹出规则：
* 若```qmax```头部等于```i-w```表示队列头应该出窗口，弹出队头。

每个下标最多进、出```qmax```一次，复杂度O(n)。

```cpp
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
```