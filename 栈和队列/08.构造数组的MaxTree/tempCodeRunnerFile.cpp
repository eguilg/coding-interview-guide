// 找每个数右边比它大的第一个，并且与左边比他大的第一个比较，去最小的
    for(int i = arr.size()-1; i >= 0; --i)
    {
        while (!s.empty() && arr[s.top()] <= arr[i])
        {
            s.pop();
        }
        if (!s.empty() && (arr[parents[i]] > arr[s.top()]) || parents[i] == -1){
            parents[i] = s.top();
        }
        if (parents[i] == -1)
        {
            root_idx = i;
        }
        s.push(i);
    }