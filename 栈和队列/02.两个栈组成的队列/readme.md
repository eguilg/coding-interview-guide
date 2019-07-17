# 由两个栈组成的队列
【题目】编写一个类，用两个栈实现队列，支持队列的基本操作，push pop front back

【难度】虎

## 方案一
两个栈，一个作为压入栈```stackPush```，在压入数据时只往这个栈中压入；另一个作为弹出栈```stackPor```，在弹出数据时只从这个栈弹出。

因为数据先压入```stackPush```，顺序是先进后出的，再将它们压入```stackPop```最后再弹出的时候，顺序就还原了，即:

先进后出->先出后进->先进后出。

例如1~5的压入弹出：
* 压入```stackPush```: 1 2 3 4 5
* 弹出```stackPush```并且压入```stackPop```:5 4 3 2 1
* 弹出```stackPop```: 1 2 3 4 5

但是压入弹出的过程必须遵循两条规则：
1. 如果要向```stackPop```中压入数据，必须一次性将```stackPush```里的数据全部压入。
2. 如果```stackPop```不为空，则不能向其中压入数据。

如果违反1，即```stackPush```中的数据只有部分压入了```stackPop```，那么如果在这次操作后有新的数据压入```stackPush```，就相当于在队列中间插入了元素。

如果违反2，相当于在队列的头部插入了数据。

压入```stackPop```的时机: 

push pop front 任一均可
```cpp
template<class T>
class queueByStack{
private:
    stack<T> stackPush;
    stack<T> stackPop;
    T back_val;
public:
    queueByStack(){}
    ~queueByStack(){}

    void push(T val)
    {
        stackPush.push(val);
        back_val = val;
    }

    T pop(){
       assert(!stackPop.empty() || !stackPush.empty());
       if (stackPop.empty())
       {
           back_val = stackPush.top();
           while(!stackPush.empty()){
               stackPop.push(stackPush.top());
               stackPush.pop();
           }
       }
       T ret = stackPop.top();
       stackPop.pop();
       return ret;
    }

    T& front(){
        assert(!stackPop.empty() || !stackPush.empty());
        if (stackPop.empty())
        {
           while(!stackPush.empty()){
               stackPop.push(stackPush.top());
               stackPush.pop();
           }
       }
       return stackPop.top();;
    }

    T& back(){
        assert(!stackPop.empty() || !stackPush.empty());
        return back_val;
    }

    bool empty()
    {
        return (stackPop.empty() && stackPush.empty());
    }
};
```