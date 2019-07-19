# include <stack>
# include <iostream>
# include <assert.h>
# include <limits.h>
using namespace std;

/***
 * 方案1
 */
class minStack1 {
private:
    stack<int> stackData;
    stack<int> stackMin; 

public:
    minStack1(){};
    ~minStack1(){};
    void push(int val){
        // 在stackMin为空或者新值<=当前最小值时，push stackMin
        if (stackMin.empty() || val <= getMin()){
            stackMin.push(val);
        }
        // stackData中存入新值
        stackData.push(val);
    }
    int pop()
    {
        assert(!stackData.empty());
        int ret = stackData.top();
        // 如果当前出栈的元素就是当前最小值，则最小值也出栈出栈
        if (ret == getMin())
        {
            stackMin.pop();
        }
        // 数据出栈
        stackData.pop();
        return ret;
    }

    int getMin(){
        assert(!stackMin.empty());
        return stackMin.top();
    }
};

/***
 * 方案2
 */
class minStack2 {
private:
    stack<int> stackData;
    stack<int> stackMin; 

public:
    minStack2(){};
    ~minStack2(){};
    void push(int val){
        // 在stackMin为空或新值小于等于当前最小值 push stackMin
        if (stackMin.empty() || val <= getMin()){
            stackMin.push(val);
        } else {     //新值大于min，再push一次min
            stackMin.push(getMin());
        }
        // stackData中存入新值
        stackData.push(val);
    }
    int pop()
    {
        assert(!stackData.empty());
        int ret = stackData.top();
        // 最小值出栈
        stackMin.pop(); 
        // 数据出栈
        stackData.pop();
        return ret;
    }

    int getMin(){
        assert(!stackMin.empty());
        return stackMin.top();
    }
};

/***
 * 方案3
 */
class minStack3{
private:
    stack<int> stackDiff;
    long cur_min = long(INT_MAX) + 1;

public:
    minStack3(){};
    ~minStack3(){};

    void push(int val){
        if (cur_min > INT_MAX)
        {
            cur_min = val;
        } else {
            stackDiff.push(val - (int)cur_min);
            if (stackDiff.top() < 0)
            {
                cur_min = val;
            }
        }
    }

    int pop(){
        assert(!stackDiff.empty() || cur_min <= INT_MAX);
        int ret;
        if (stackDiff.empty())
        {
            ret = cur_min;
            cur_min = long(INT_MAX) + 1;
        } else if (stackDiff.top() <= 0){
            ret =  int(cur_min);
            cur_min = cur_min - (long)stackDiff.top();
            stackDiff.pop();
        } else {
            ret = int(cur_min) + stackDiff.top();
            stackDiff.pop();
        }
        return ret;
    }

    int top(){
        assert(!stackDiff.empty() || cur_min <= INT_MAX);
        if (stackDiff.empty() || stackDiff.top() <= 0){
            return int(cur_min);
        }
        return int(cur_min) + stackDiff.top();
    }

    int getMin(){
        assert(!stackDiff.empty() || cur_min <= INT_MAX);
        return cur_min;
    } 
};
int main()
{
    minStack1 ms1;
    int data[6] = {5, 4, 7, 2, 3, 1};
    for (int d: data)
    {
        ms1.push(d);
        cout<<ms1.getMin()<<endl;
        if ((d & 1) == 0){
            ms1.pop();
        }
    }
    cout << "------" << endl;
    minStack2 ms2;
    
    for (int d: data)
    {
        ms2.push(d);
        cout<<ms2.getMin()<<endl;
        if ((d & 1) == 0){
            ms2.pop();
        }
    }

    cout << "------" << endl;
    minStack3 ms3;
    
    for (int d: data)
    {
        ms3.push(d);
        cout<<ms3.getMin()<<endl;
        if ((d & 1) == 0){
            ms3.pop();
        }
    }
    return 0;
}