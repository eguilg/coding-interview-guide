# 用一个栈实现另一个栈的排序
【题目】将整型栈从顶到底按从大到小顺序排序，只能申请另一个栈和新的变量。

【难度】狼

## 方案一
这是一个单调栈的问题，这里我们用```help```表示申请的辅助栈，这个辅助栈是一个单调栈，即新插入其中的元素只能比当前栈顶小(或等)。

在原栈上不断pop，记弹出的为```cur```

* 若```cur <= help.top()```, 压```cur```入```help```。
* 若```cur > help.top()```， 将```help```中元素逐个弹出压入原始栈，直到```cur <= help.top()```,再压```cur```入```help```。

直到全部元素都压入```help```中， 再逐一压入原始栈即可。

```cpp
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
```