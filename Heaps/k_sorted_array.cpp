/* 
	Given an array where the elements are k sorted. It means that each element is at most k places
	away from its sorted position. Sort such an array.

	Input: vector of int
	Output: 1d sorted vector
	
	Solution:
		Since each element is at most k places away, that means the first element is also atmost k places
		away, so we atleast need to get the first k elements. So we use a min-heap of size 'k'. We push the first
		'k' elements in it, when we are at k+1th element we can just pop the min element and push to the 0th index.
		Similarly we do the same for the rest. When the heap is empty we are done.

		TC: O(nlogk), k: heap size, n: no. of elements
		SC: O(k) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

// sorts k sorted array
vector<int> kSortedData(vector<int>& arr, int k) {
	// make a min-heap
	priority_queue<int, vector<int>, greater<>> min_heap;

	// insert first k elements
	for(int i = 0; i < k; i++) 
		min_heap.emplace(arr[i]);
	
	int write_idx = 0;
	int i = k;
	// now do for the rest of the elements
	while(!min_heap.empty()) {
		arr[write_idx++] = min_heap.top();
		min_heap.pop();

		// push the current element
		if(i < arr.size())
			min_heap.emplace(arr[i++]);
	}

	return arr;
}

// overloading << for directly viewing the vector elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a << " ";
	cout << endl;
}

int main() {
	vector<int> arr = {3, -1, 2, 6, 24, 15, 28};
							
	cout << kSortedData(arr, 2);
	return 0;
}
