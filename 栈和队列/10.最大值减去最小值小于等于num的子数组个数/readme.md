# 最大值减去最小值小于等于num的子数组个数
【题目】给定数组arr和整数num，返回共有多少个子数组满足：

```max(arr[i:j]) - min(arr[i:j]) <= num```

【要求】O(N)时间。

【难度】鬼

## 方案一
暴力方法，所有子数组共O(N^2)个，然后遍历每个子数组找到最大最小值判断是否满足条件。一共O(N^3)。

首先```check_valid```检查```arr[i:j]```是否满足要求：

```cpp
bool check_valid(vector<int>& arr, size_t i, size_t j, int num){
    int max_n = arr[i], min_n = arr[i];
    long max_diff = 0;
    bool flag = true;
    for (int k = i; k < j; ++k){
        max_n = max(max_n, arr[k]);
        min_n = min(min_n, arr[k]);
        max_diff = max(long(max_n) - long(min_n), max_diff);
        if (max_diff > num){ 
            flag = false;
            break;
        } 
    }
    return flag;
}
```

然后是遍历检查所有子数组：

```cpp
int getInNum1(vector<int>& arr, int num){
    size_t n = arr.size();
    int count = 0;
    for (size_t i = 0; i < n; ++i){
        for (size_t j = i+1; j <= n; ++j){ 
            if (check_valid(arr, i, j, num)){
                count++;
            }
        }
    }
    return count;
}
```

## 方案二

* 对于一个子数组如果满足题目要求，那么该子数组的所有子数组也满足要求。
* 对于一个子数组如果不满足题目要求，那么所有包含该子数组的子数组也都不满足要求。

那么可以设置两个指针```i,j```表示当前字数组，从```i=j=0```开始（此时max-min=0, 满足条件）让```j```不断向右扩张，同时判断是否满足条件，一旦不满足条件，```j```停止向右，此时所有以```arr[i]```开头的子数组总满足条件的共```(j-i)```个。然后```i```右移一位，即计数所有以新的```arr[i]```开头的子数组有多少满足条件的，继续重复直到遍历完。

这里```i,j```移动遍历数组是O(N)操作，然后每次移动后遍历当前子数组判断是否满足条件是O(N)，也就是O(N^2)。

```cpp
int getInNum2(vector<int>& arr, int num){  
    int count = 0;
    size_t i = 0, j = 0, n = arr.size(); 
    while(i != n){
        while(j != n && check_valid(arr, i, j+1, num)){
            ++j;
        }
        count += j - i;
        ++i;
    }
    return count;
}
```

## 方案三
延续方案二的方法，每次移动都遍历来检查是否符合条件是会有很多重复计算的。回想07题“生成窗口最大值数组”中使用单调双端队列来实时获取子数组的最大值(最小值)，可以把原来O(N)的```check_valid```优化为O(1)的取队头比较操作。最终从一开始的O(N^3)变成了O(N)。

```cpp
int getInNum3(vector<int>& arr, int num){
    int count = 0;
    int i = 0, j = 0, n = arr.size();
    list<size_t> qmax, qmin;

    while (i != n){
        while (j != n){
            while (!qmax.empty() && arr[j] >= arr[qmax.back()]){
                qmax.pop_back();
            }
            qmax.push_back(j);
            while (!qmin.empty() && arr[j] <= arr[qmin.back()]){
                qmin.pop_back();
            }
            qmin.push_back(j);
            if (long(arr[qmax.front()]) - long(arr[qmin.front()]) > num){
                break;
            }   
            ++j;
        }
        if (qmax.front() == i){
            qmax.pop_front();
        }
        if (qmin.front() == i){
            qmin.pop_front();
        }
        count += j - i;
        ++i;
    }
    return count;
} 
```
