# include <bits/stdc++.h>
# include <limits>
using namespace std;

/*******************************
方案一，维护大根堆
****************************** */

/**
 * 输入堆数组heap，带插入元素val，heap末尾空位index
 * 将输入元素val向上移动，直到合适的位置
 */
void heapInsert(vector<int>& heap, int val, int index) {
    heap[index] = val;
    while (index != 0)
    {
        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index]) {
            swap(heap[parent], heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

/**
 * 调整index位置的元素到合适的位置
 */
void heapify(vector<int>& heap, int index, int heapSize) {
    int left = index*2 + 1;
    int right = index*2 + 2;
    int largest = index;
    while (left < heapSize) {
        if (heap[left] > heap[index]) {
            largest = left;
        }
        if (right < heapSize && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != index) {
            swap(heap[index], heap[largest]);
        } else {
            break;
        }
        index = largest;
        left = index * 2 + 1;
        right = index * 2 + 1;
    }
}

vector<int> minKbyHeap(vector<int>& arr, int k) {
    if (k >= arr.size()) {
        return arr;
    }
    if (k < 1) {
        return vector<int>();
    }
    vector<int> heap(k, INT_MAX);
    for (int i = 0; i < k; ++i) {
        heapInsert(heap, arr[i], i);
    }
    for (int i = k; i < arr.size(); ++i) {
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];
            heapify(heap, 0, k);
        }
    }
    return heap; 
}


/***********************************
 * 方案二， BFPRT 找到第k小的元素
 ***********************************/
vector<int> partition(vector<int>& arr, int begin, int end, int pivot) {
    
    int small = begin - 1;
    int big = end + 1;
    int cur = begin;
    
    while (cur != big) {
        if (arr[cur] < pivot) {
            swap(arr[cur++], arr[++small]);
        } else if (arr[cur] > pivot) {
            swap(arr[cur], arr[--big]);
        } else {
            cur++;
        }
    }
    vector<int> range = {small + 1, big - 1};
    
    return range;
}
int select(vector<int>& arr, int begin, int end, int i);
void insertion_sort(vector<int> arr, int begin, int end) {
    for (int i = begin + 1; i != end+1; i++) {
        for (int j = i; j != begin; j--) {
            if (arr[j-1] > arr[j]){
                swap(arr[j-1], arr[j]);
            } else {
                break;
            }
        }
    }
}
int getMedian(vector<int>& arr, int begin, int end) {
    insertion_sort(arr, begin, end);
    int sum = end + begin;
    int mid = (sum / 2) + (sum % 2);
    return arr[mid];
}
int medianOfMedians(vector<int>& arr, int begin, int end) {
    int num = end - begin + 1;
    int offset = num % 5 == 0? 0 : 1;
    vector<int> mArr(num / 5 + offset, 0);
    for (int i = 0; i < mArr.size(); ++i) {
        int beginI = begin + i * 5;
        int endI = beginI + 4;
        mArr[i] = getMedian(arr, beginI, min(end, endI));
    }
    return select(mArr, 0, mArr.size()-1, mArr.size()/2);
}




int medianOfTree(vector<int>& arr, int begin, int end) {
    if (end - begin < 2) {
        return arr[end];
    }
    int mid = arr[(begin + end) / 2];
    int left = arr[begin];
    int right = arr[end];
    if ((mid >= left && mid <= right) || (mid >= right && mid <= left)){
        return mid;
    }
    else if ((left >= mid && left <= right) || (left >= right && left <= mid)){
        return left;
    }
    else {
        return right;
    }
}

int select(vector<int>& arr, int begin, int end, int i){
    if (begin == end) {
        return arr[end];
    }
    
    int pivot = medianOfTree(arr, begin, end);
    vector<int> pivotRange = partition(arr, begin, end, pivot);
    if (i <= pivotRange[1] && i >= pivotRange[0]) {
        return arr[i];
    } else if (i < pivotRange[0]) {
        return select(arr, begin, pivotRange[0] - 1, i);
    } else {
        return select(arr, pivotRange[1] + 1, end, i);
    }
}

int BFPRT(vector<int> arr, int k) {
    // 传入的不是引用而是值
    return select(arr, 0, arr.size()-1, k-1);
}


vector<int> minKbyBFPRT(vector<int>& arr, int k) {
    if (k >= arr.size()) {
        return arr;
    }
    if (k < 1) {
        return vector<int>();
    }
    int minK = BFPRT(arr, k);
    vector<int> ret(k, 0);
    int idx = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < minK){
            ret[idx++] = arr[i];
        }
    }
    for (; idx < ret.size(); ++idx){
        ret[idx] = minK;
    }
    return ret;
}
int main(){
    vector<int> arr(100000000, 0);
    for (int i = 0; i < arr.size(); ++i){
        arr[i] = rand();
    }
    clock_t start1 = clock();
    vector<int> minK1 = minKbyHeap(arr, 10);
    clock_t end1 = clock();
    vector<int> minK2 = minKbyBFPRT(arr, 10);
    clock_t end2 = clock();

    cout << end1 - start1 <<endl;
    cout << end2 - end1 <<endl;

    for (auto a : minK2) {
        cout << a << " ";
    }
    cout << endl;
}