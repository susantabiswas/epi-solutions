/* 
	Given a max-heap in array form. Find the k largest elements from the heap without modifying the array.

	Input: int array
	Output: k largest int vector
	
	Solution:
		We can use a max-heap. The root element is sure to be the largest, so push it in heap.
		Now every time we pop the max element from heap and add to result vector and for the 
		max element, we push child nodes. Since inside the tree we should move towards the side
		which has larger parent elements so that we get larger nodes. This is supported by the fact that in heap, the parent is atleast
		greater/equal than its children. So each time we add only child of current largest node.
		
		
		TC: O(klogk),  
		SC: O(k) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

struct HeapElement{
	int data;
	int idx;
	
	HeapElement(int data, int idx) : data(data), idx(idx) {}
};

// finds the k largest heap elements
vector<int> kLargestHeapElements(vector<int>& heap, int& k) {
	if(heap.size() < 1 || k <= 0)
		return vector<int>{};

	// max-heap
	priority_queue<HeapElement, vector<HeapElement>, function<bool(HeapElement, HeapElement)>> 
		max_heap([](const HeapElement& a, const HeapElement& b)->bool{
			return a.data < b.data;
		});
	// start with the root of input heap
	max_heap.emplace(HeapElement{heap[0], 0});

	vector<int> k_largest;
	int i = 0;
	HeapElement curr_largest = HeapElement{heap[0], 0};
	
	while(!max_heap.empty() && i < k) {
		// take the current largest 
		curr_largest = max_heap.top();
		max_heap.pop();
		
		// add its child nodes
		// left child
		if((2 * curr_largest.idx  + 1) < heap.size()) 
			max_heap.emplace(HeapElement{heap[2 * curr_largest.idx  + 1], 2 * curr_largest.idx  + 1});
		// right child
		if((2 * curr_largest.idx  + 2) < heap.size())
			max_heap.emplace(HeapElement{heap[2 * curr_largest.idx  + 2], 2 * curr_largest.idx  + 2});
		
		// add to results
		k_largest.emplace_back(curr_largest.data);
		++i;
	}

	return k_largest;
}

// overloading << for directly viewing the vector elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a << ", ";
	cout << endl;
}

int main() {
	int k = 3;
	vector<int> heap = {562, 314, 401, 28, 156, 359, 271, 11, 3};
	cout << kLargestHeapElements(heap, k);
	return 0;
}
