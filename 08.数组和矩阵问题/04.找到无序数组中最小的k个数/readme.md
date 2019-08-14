# 找到无序数组中最小的k个数

【题目】给定一个无序数组arr，找到其中最小的k个数。

【难度】O(Nlogk) 虎 | O(N) 神

## 方案一
一直维护一个有k个数的大根堆，这个堆中存放的是目前选出的k个最小数，堆顶是k个数中最大的那个。遍历数组的过程中不断与堆顶比较，若比堆顶小，则将堆顶调整为当前元素，然后从堆顶调整整个堆。
整个过程如下：
```cpp
vector<int> minKbyHeap(vector<int>& arr, int k) {
    if (k < 1) {
        return vector<int>();
    }
    if (k > arr.size()) {
        return arr;
    }
    // 初始化大小为k的堆，存无限大
    vector<int> heap(k, INT_MAX);
    // 先插入前k个元素
    for (int i = 0; i < k; ++i) {
        heapInsert(heap, arr[i], i);
    }
    for (int i = k; i < arr.size(); ++i) {
        // 对于后面的元素，如果比堆顶要小，则将堆顶置为当前元素，并调整堆
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];
            heapify(heap, 0, k);
        }
    }
}
```
堆的插入
```cpp
void heapInsert(vector<int>& heap, int val, int index) {
    heap[index] = val;
    while (index != 0) {
        int parent = (index - 1) / 2;
        
        if (heap[parent] < heap[index]) {
            // 如果父亲更小，则跟父亲交换位置
            swap(heap[parent], heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}
```
堆的调整
```cpp
void heapify(vector<int>& heap, int index, int heapSize) {
    // 左右孩子
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;
    while (left < heapSize) { // 当还有孩子时
        // 找到一家三口中最大的
        if (heap[left] > heap[index]) {
            largest = left;
        }
        if (right < heapSize && heap[right] > heap[index]) {
            largest = right;
        }
        // 如果不是父亲最大，就把父亲换跟最大的替换
        if (largest != index) {
            swap(heap[largest], heap[index]);
        } else { //父亲最大就满足要求了
            break;
        }
        //接着向下遍历
        index = largest;
        left = index*2 + 1;
        right = index*2 + 2;
    }
}
```
## 方案二——使用BFPRT算法
*显而易见的是，如果我们找到了第k小的数，那么想求arr中最小的k个数，就是遍历一次数组的工作量而已。*
BFPRT算法的作用就是找到数组中第k小的数，假设其形式为`BFPRT(arr, k)`过程如下：
1. 将arr中的n个元素划分成n/5组，每组5个元素，最后不够5个也为一组(n%5个)。
2. 对每个组进行插入排序，只针对每个组最多5个元素之间的组内排序，组与组之间不排序。排序后找到每组的中位数，若组的元素个数为偶数，规定找下中位数。
3. 对于步骤2中找到的`n/5`个中位数，让这些中位数组成一个新的数组，即为`mArr`。递归调用`BFPRT(mArr, mArr.size() / 2)`，其意义是找到`mArr`数组中的中位数，即`mArr`中第`(mArr.size() / 2)`小的数。
4. 假设步骤3中递归调用`BFPRT(mArr, mArr.size() / 2)`后，返回的数为x。根据这个x划分整个数组(partition过程)，即：在arr中比x小的都在x左边，比x大的都在x右边。划分完成后，x在arr中的位置记为i。
5. 若`i+1==k`直接返回，

    * 若`i+1 < k`说明x位置在要找的数左边，应该在x的右边继续找，递归调用`BFPRT(arr[x+1:], k-i)`
    * 若`i+1 > k`说明x位置在要找的数左边，应该在x的左边继续找，递归调用`BFPRT(arr[:x], k)`



