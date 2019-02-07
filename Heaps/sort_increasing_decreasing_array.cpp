/* 
	There is an array which has elements which increase in order and then start decreasing. This can happen multiple
	time. Sort such an array.

	Input: vector of int
	Output: 1d sorted vector
	
	Solution:
		First we segregate the vectors into individual sorted arrays and then we
		use the algorithm for merging multiple sorted vectors. We use a 2d vector for storing the sorted 
		vectors.
		Increasing vector can be added directly. For decreasing vector we first need to reverse the elements then add.

		For merging sorted vectors:
			For 'k' no. of vectors, we make a min-heap of 'k' size. Initially
			it is filled with first entry from each vector. Every time we pop the smallest
			from the heap and push the next element of the vector from which the min was popped.
			Since the files are having sorted content so we are only pushing the elements
			which are smaller and then finding the smallest amongst them each time.

		TC: O(nlogk), k: no. of vectors, n: total sequences
		SC: O(k) 
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <functional>
using namespace std;

struct VectorIterator{
	vector<int>::const_iterator curr;	// for current vector element
	vector<int>::const_iterator last; // for saving vector end
	
	bool operator>(const VectorIterator& b) const{
		return 	*curr > *(b.curr);
	}
};

// merges multiple sorted vector into a single vector
vector<int> mergeMultipleSortedvectors(vector<vector<int>>& arr) {
	vector<int> sorted_vector;
	// num of vectors
	const int num_vectors = arr.size();

	// min-heap of size equal to num of vectors, here we use lambda function for comparator
	// we can use greater<> also, since '<' has been overloaded already in structure
	priority_queue<VectorIterator, vector<VectorIterator>, function<bool(VectorIterator, VectorIterator)>>
		min_heap([](const VectorIterator& a, const VectorIterator& b)->bool{
			return *(a.curr) > *(b.curr);
		});
	
	// for each vector, we put its first and last iterators, this helps
	// to keep track of which vector element was popped 
	for(const vector<int>& a: arr) {
		min_heap.emplace(VectorIterator{a.cbegin(), a.cend()});	
	}
	
	// now we keep popping the smallest element from heap untill all the 
	// vector elements are finished
	while(!min_heap.empty()) {
		auto min_el = min_heap.top();
		// pop the heap min
		min_heap.pop();

		// now push the next element from the vector from
		// which the element was popped
		if(min_el.curr != min_el.last) {
			sorted_vector.emplace_back(*(min_el.curr));
			min_heap.emplace( VectorIterator{ next(min_el.curr), min_el.last });
		}
			
	}
	
	return sorted_vector;
}

// sorts increasing decreasing vector elements
vector<int> sortIncreasingDecreasingElements(vector<int>& arr) {
	// for storing multiple sorted arrays from single array
	vector<vector<int>> multiple_sorted_arrays;
	
	vector<int> :: iterator start = arr.begin();
	vector<int> :: iterator last = arr.begin();

	bool reverse_arr = false;

	for(int i = 0; i < arr.size() - 1; i++, last++) {
		// if next element is greater it means decreasing list has started
		if(arr[i] > arr[i+1]) {
			multiple_sorted_arrays.emplace_back(vector<int>(start, last + 1));
			// first element for next array
			start = last + 1;
		}
		else if(arr[i] <= arr[i+1]) {
			// reverse the subvector first
			reverse(start, last + 1);
			multiple_sorted_arrays.emplace_back(vector<int>(start, last + 1));
			// first element for next array
			start = last + 1;
		}
	}

	return mergeMultipleSortedvectors(multiple_sorted_arrays);
}

// overloading << for directly viewing the vector elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a << " ";
	cout << endl;
}

int main() {
	vector<int> arr = {-1, 0, 5, 89, 7, 2, 5, 7, 9, 10, -22, 67, 89, 91, 100, 2, 8, 9, 10, 15, 77};
							

	cout << sortIncreasingDecreasingElements(arr);
	return 0;
}
