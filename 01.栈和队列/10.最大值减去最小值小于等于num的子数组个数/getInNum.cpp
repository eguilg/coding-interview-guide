# include <bits/stdc++.h>
# include <limits.h>
using namespace std;

bool check_valid(vector<int>& arr, size_t i, size_t j, int num)
{
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

int main()
{
    vector<int> arr = {1,2,3,9};
    cout << getInNum1(arr, 4) << endl;
    cout << getInNum2(arr, 4) << endl;
    cout << getInNum3(arr, 4) << endl;
}