# include <bits/stdc++.h>

using namespace std;

// 移除并返回栈底的元素 O(2n)
template <class T>
T getAndRemoveLastElement(stack<T>& s){
    T result = s.top(); 
    s.pop();
    if (s.empty())
    {
        return result;
    } else {
        T last = getAndRemoveLastElement(s);
        s.push(result);
        return last;
    }
}

template <class T>
void reverseStack(stack<T>& s){
    if (s.empty())
    {
        return;
    }
    T i = getAndRemoveLastElement(s);
    reverseStack(s);
    s.push(i);
}

int main()
{
    int data[5] = {1,2,3,4,5};
    stack<int> s;
    for (int d: data)
    {
        s.push(d);
    }

    reverseStack(s);
    
    while(!s.empty())
    {
        cout<<s.top()<<endl;
        s.pop();
    }
    return 0;
}