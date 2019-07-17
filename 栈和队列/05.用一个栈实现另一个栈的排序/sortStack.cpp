# include <bits/stdc++.h>

using namespace std;

void sortStack(stack<int> &s)
{
    stack<int> help;
    int cur;
    while (!s.empty())
    {
        cur = s.top();
        s.pop();
        while (!help.empty() && cur > help.top())
        {
            s.push(help.top());
            help.pop();
        }
        help.push(cur);
    }

    while(!help.empty())
    {
        s.push(help.top());
        help.pop();
    }
}

int main()
{
    int data[5] = {4,1,5,2,7};
    stack<int> s;
    for(int d:data)
    {
        s.push(d);
    }

    sortStack(s);
    while(!s.empty())
    {
        cout<< s.top()<<endl;
        s.pop();
    }
}