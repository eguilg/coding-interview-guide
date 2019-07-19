# include <bits/stdc++.h> 

using namespace std;

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


int main()
{
    int aa[5] = {1,2,3,4,5};
    queueByStack<int> q;
    for(int a : aa)
    {
        q.push(a);
    }

    while (!q.empty())
    {
        cout << q.front()<< endl;
        q.pop();
    }
    return 0;

}

