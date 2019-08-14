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


int main(){
    vector<int> arr = {1,4,1,3,4,8,9};
    vector<int> minK = minKbyHeap(arr, 5);
    for (auto a : minK) {
        cout << a << endl;
    }
}