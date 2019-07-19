# 仅用递归函数和栈操作逆序一个栈
【题目】只用递归和栈操作逆序一个栈，不可用其他数据结构存储。

【难度】虎

## 方案一
这个题的递归真是让人头皮发麻。主要是两个函数

* ```getAndRemoveLastElement()```

    用来移除并返回栈底的元素。每次调用都是先将栈顶出栈，如果出栈后栈空了，那就直接返回这个栈顶；如果栈没空，那就接着对栈内剩下的元素进行同样的操作，直到到达栈底，然后再把除了栈底之外的所有元素按照原来的顺序压栈，栈底元素返回到调用栈顶层。例子：
```py
    1 2 3 4 
    
    -> 1 2 3 | 4

    -> 1 2 | 3 | 4

    -> 1 | 2 | 3 | 4

    -> 2 | 3 | 4 , return 1
    
    -> 2 3 | 4 , return 1

    -> 2 3 4 , return 1
```
* ```reverseStack()```

    用来反转栈内元素。每次调用都是先调用```getAndRemoveLastElement()```移除栈底元素，然后递归将栈内剩下元素反转，再将之前的栈底元素压到栈顶，完成反转。例子：
```py
    1 2 3 4 -> 2 3 4 | 1 -> 4 3 2 1

    2 3 4 -> 3 4 | 2 -> 4 3 2 
    
    3 4 -> 4 | 3 -> 4 3
```

```cpp
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
```