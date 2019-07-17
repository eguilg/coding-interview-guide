# 设计一个有getMin功能的栈
【题目】设计一个特殊的栈，在实现栈的基本功能的基础上，再实现返回栈中最小元素的操作。

【要求】pop、push、getMin 均为O(1) 。

【难度】狼


## 方案一 
双栈实现，第一个栈保存数据，第二个栈保存每一步的最小值。

入栈：若stackMin为空 或者 getMin()<= val，直接将新值加入stackMin。

出栈：若当前出栈的元素就是最小值，则stackMin也要出栈一次，否则只有数据栈出栈。

getMin: 直接返回stackMin栈顶。
``` cpp
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
```

## 方案二 
也是双栈实现，第一个栈保存数据，第二个栈保存每一步的最小值，不同的是stackMin会重复存储最小值，这样出栈的时候不用判断，同步出栈即可。

入栈：
1. 若stackMin为空 或者 getMin()<= val，直接将新值加入stackMin。
2. 若getMin() > val， 那就再将当前最小值入栈stackMin次

出栈：直接两栈同步出栈

getMin: 直接返回stackMin栈顶。
``` cpp
class minStack2 {
private:
    stack<int> stackData;
    stack<int> stackMin; 

public:
    minStack2(){};
    ~minStack2(){};
    void push(int val){
        // 在stackMin为空push stackMin
        if (stackMin.empty()){
            stackMin.push(val);
        } else if (val <= getMin()){ //新值小于等于min时
            stackMin.push(val);
        } else{     //新值大于min，再push一次min
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
```
## 方案三 
只需要一个栈实现，栈中存储每个元素和上一步的栈内最小值的差，另外用一个变量存储当前的最小值。 

初始状态： 栈为空 而且 最小值>INT_MAX。

入栈第一个元素时： 栈仍为空，但是当前最小值为该元素

入栈： 
1. 如果当时栈为空 且 cur_min无效(>INT_MAX),设置```cur_min = val```
2. 如果栈不为空，stackDiff中插入```val - cur_min```，

    若```val - cur_min < 0```，即当前插入的是新的最小值，设置```cur_min = val ```

出栈：
1. 若栈为空，则返回值为```cur_min```，然后另```cur_min```为初始值(```INT_MAX+1```)
2. 若```stackDiff.top() <= 0```，表示当前栈顶为最小值， 返回```cur_min```, 更新```cur_min```为上一次的最小值即```cur_min - stackDiff.top()```, 然后```stackDiff.pop()```
3. 若```stackDiff.top() > 0```, 则当前栈顶出栈之后最小值不会变化，返回当前栈顶元素```cur_min + stackDiff.top()```, 然后```stackDiff.pop()```

getMin: 判断是否空栈，非空的话直接返回```cur_min```即可
```cpp
class minStack3{
private:
    stack<int> stackDiff;
    long cur_min = long(INT_MAX) + 1;

public:
    minStack3(){};
    ~minStack3(){};

    void push(int val){
        if (cur_min > INT_MAX && stackDiff.empty())
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
        assert(stackDiff.empty() && cur_min > INT_MAX);
        int ret;
        if (stackDiff.empty())
        {
            ret = cur_min;
            cur_min = INT_MAX + 1;
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

    int getMine(){
        assert(stackDiff.empty() && cur_min > INT_MAX);
        return cur_min;
    } 
};
```