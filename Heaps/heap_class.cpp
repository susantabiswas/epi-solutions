/*
    Generic Heap class Implementation.

        For heap of size 'n':
            TC: Push: O(logn)
                Pop: O(logn)
                Heapify: O(n)
                Max/Min: O(1)

            SC: O(n) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

typedef enum { MIN_HEAP, MAX_HEAP } HeapType;

template<typename T>
class Heap {
private:
    vector<T> heap_;
    int capacity_;
    int num_heap_elements_;
    HeapType heap_type_;
    const int RESIZE_FACTOR = 2;

public:
    // Constructor
    // creates a heap with elements from vector and the capacity 
    // is initialised to twice vector size
    Heap(vector<T> arr, HeapType type) {
        // no. of elements in heap
        num_heap_elements_ = 0;
        // min or max heap
        heap_type_ = type;

        for (const auto& a : arr)
            heap_.emplace_back(a);
        num_heap_elements_ = heap_.size();

        struct greater<T> comp_greater;
        struct less<T> comp_less;

        // set the comparator acc. to heap type
        if (heap_type_ == MAX_HEAP)
            comp_greater = greater<T>();
        else if (heap_type_ == MIN_HEAP)
            comp_less = less<T>();

        // now heapify the vector, starting with the first non-leaf node
        // since leaf nodes always satisfy heap property
        // start percolating down
        for (int i = (num_heap_elements_ - 1) / 2; i >= 0; i--) {
            if (heap_type_ == MAX_HEAP)
                percolateDown(i, comp_greater);
            else if (heap_type_ == MIN_HEAP)
                percolateDown(i, comp_less);
        }
    }

    // Constructor
    // creates heap with just the size and type
    Heap(int capacity, HeapType type) {
        // no. of elements in heap
        num_heap_elements_ = 0;
        // min or max heap
        heap_type_ = type;
        capacity_ = capacity;
        // set heap to current capacity
        heap_.resize(capacity_);
    }

    // for pushing element to heap
    void Push(T data) {
        // when heap is full
        if (num_heap_elements_ == capacity_) {
            // resize the vector for heap
            resizeHeap();
        }

        // add the element at last
        // then percolate from there to all the way up
        ++num_heap_elements_;
        heap_[num_heap_elements_ - 1] = data;

        // while the parent is not satisfying the heap
        // property, swap currrent element with parent
        // till the time current element is at its correct position
        int i = num_heap_elements_ - 1;
        if (heap_type_ == MAX_HEAP) {
            while (i > 0 && (heap_[getParentIndex(i)] < heap_[i])) {
                int parent_idx = getParentIndex(i);
                swap(heap_[parent_idx], heap_[i]);
                i = parent_idx;
            }
        }
        else if (heap_type_ == MIN_HEAP) {
            while (i > 0 && heap_[getParentIndex(i)] > heap_[i]) {
                int parent_idx = getParentIndex(i);
                swap(heap_[parent_idx], heap_[i]);
                i = parent_idx;
            }
        }    
    }

    // for deleting element from heap
    /*
        Heap deletion: only the root element is deleted.
        We swap the root element with last element in vector, then make the
        heap size reduced by 1. Then to fix the distruption caused by
        swapping we percolate from root
    */
    T Pop() {
        // check if heap is empty or not
        if (isEmpty())
            throw length_error("Heap is empty");

        // swap the first with last 
        swap(heap_[0], heap_[num_heap_elements_ - 1]);

        T popped_data = heap_[num_heap_elements_ - 1];
        // decrease the heap elements count by 1
        --num_heap_elements_;

        // percolate down to ensure heap property is maintained
        if (heap_type_ == MAX_HEAP)
            percolateDown(0, greater<T>());
        else if (heap_type_ == MIN_HEAP)
            percolateDown(0, less<T>());

        return popped_data;
    }

    // get the root element of heap
    T Top() {
        if (isEmpty())
            throw length_error("Heap is empty");
        return heap_[0];
    }

    // checks if heap is empty
    bool isEmpty() {
        return num_heap_elements_ == 0;
    }

    // returns the index of parent
    int getParentIndex(const int& i) {
        // either heap is empty or index is out of bound
        if (isEmpty() || (i <= 0) || (i >= num_heap_elements_))
            return -1;
        return (i - 1) / 2;
    }

    // returns the index of left child
    int getLeftChildIndex(const int& i) {
        // either heap is empty or index is out of bound
        if (isEmpty() || (i < 0) || (i >= num_heap_elements_))
            return -1;
        return (2 * i + 1) < num_heap_elements_ ? (2 * i + 1) : -1;
    }

    // returns the index of right child
    int getRightChildIndex(const int& i) {
        // either heap is empty or index is out of bound
        if (isEmpty() || (i < 0) || (i >= num_heap_elements_))
            return -1;
        return (2 * i + 2) < num_heap_elements_ ? (2 * i + 2) : -1;
    }

    // for fixing the heap property in the heap
    /* The logic for fixing the heap property is that we
        check if the left or right child of current index is greater in
        case of max-heap or smaller in case of min-heap.
        If that is the case then to fix the heap property we swap that element
         with current parent, and then percolate from that index
    */
    template<typename Compare>
    void percolateDown(int idx, Compare comp) {
        // assume that current parent is saisfying heap property
        // for max heap: this will contain greatest amongst parent, left and right child
        // for min_heap: this will comtain min amongst parent, left and right child
        int heap_prop_idx = idx;

        // get left and right child
        int left = getLeftChildIndex(idx);
        int right = getRightChildIndex(idx);

        // check if the child nodes are greater/lesser than parent or not
        // compare function: max-heap: if first is greater than second returns true
        // min_heap: if first is smaller than second returns true
        if (left != -1 && comp(heap_[left], heap_[heap_prop_idx])) {
            heap_prop_idx = left;
        }
        if (right != -1 && comp(heap_[right], heap_[heap_prop_idx])) {
            heap_prop_idx = right;
        }

        // now if the current parent is not satusfying heap property
        // swap it with its child that is greater/smaller than it
        if (heap_prop_idx != idx) {
            swap(heap_[heap_prop_idx], heap_[idx]);
            // fix the lower subtrees
            percolateDown(heap_prop_idx, comp);
        }
    }

    // for expanding capacity of heap
    void resizeHeap() {
        // update current capacity
        capacity_ = capacity_ * RESIZE_FACTOR;
        heap_.resize(capacity_);
    }

    // shows heap array elements
    void showHeapArray() {
        for (int i = 0; i < num_heap_elements_; i++)
            cout << heap_[i] << " ";
        cout << endl;
    }
};


// for doing heap sort
/*
    We are doing in place sort, so we start writing from back.
    For sorting in increasing order: max_heap is used
    For sorting in decreasing order: min_heap is used
*/
template<typename T>
void heapSort(vector<T>& arr, HeapType type) {
    // heapify the  array
    Heap<T> h(arr, type);
    int write_idx = arr.size() - 1;
    int data;

    while (!h.isEmpty()) {
        // max or min data
        data = h.Pop();
        arr[write_idx--] = data;
    }
}

int main() {
    // 562, 300, 400, 29, 200, 360, 10, 4
    vector<int> arr = { 562, 300, 10, 200, 29, 360, 4, 400 };
    HeapType type = MAX_HEAP;
    Heap<int> heap(arr, type);
    cout << heap.Pop() << endl;
    heap.showHeapArray();
  
    cout << endl;
    cout << heap.Pop() << endl;
    heap.Push(21323);
    heap.showHeapArray();
    
    heapSort<int>(arr, MAX_HEAP);
    for (auto a : arr)
        cout << a << " ";

    return 0;
}
