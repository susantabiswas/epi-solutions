/* 
	There is a stream of numbers. Find the median for each instant.

	Input: stream of int
	Output: median at each instant
	
	Solution:
		Median is a number which lies between a series of numbers. If there are
		even number of integers, then it is avg of middle two terms and if it is 
		odd then it is the middle element.
		Also, elements before the median are all smaller and elements after are all 
		bigger.
		So, we need to keep track of the largest of smaller number range and the smallest
		of large number range.
		For doing this we use two heaps, max-heap keeps track of the smaller range and
		min-heap keeps track of larger numbers.
		Since there can be odd number of terms, so we keep more terms in min-heap.
		Every time a new number comes in, we insert it in one of the heaps first, then
		check which heap has more terms.
		If both are same, then median is avg of two smaller and larger terms of each heap.
		If no. of terms are different then move elements from one heap to another to balance 
		the terms on both sides. Min-heap should have 1 more term than max-heap.

		TC: O(nlogn), k: heap size, n: no. of elements
		SC: O(n) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

// finds the median of streaming integers at every instant
vector<double> showLiveMedian(istringstream* ss) {
	vector<double> medians;

	// max-heap for tracking smaller range
	priority_queue<int, vector<int>, less<>> max_heap;
	// min-heap for tracking larger range
	priority_queue<int, vector<int>, greater<>> min_heap;
	
	string token;
	int num;
	while(getline(*ss, token, ',')) {
		num = stoi(token);
		
		// if first term push to min-heap
		if(min_heap.empty())
			min_heap.emplace(num);
		else {
			// push the term acc. to which range it should belong to
			if(num >= min_heap.top())	
				min_heap.emplace(num);
			else {
				max_heap.emplace(num);
			}
		}

		// balancing the heaps
		// if the min-heap has more terms move to max-heap
		if(min_heap.size() > max_heap.size() + 1) {
			max_heap.emplace(min_heap.top());
			min_heap.pop();
		} 
		else if(max_heap.size() > min_heap.size()) {
			min_heap.emplace(max_heap.top());
			max_heap.pop();
		}

		// finding the median
		// if the number of terms is even, then avg 
		if(max_heap.size() == min_heap.size()) {
			medians.emplace_back((max_heap.top() + min_heap.top()) / 2.0);
		}
		else {	 // when the no. of terms is odd, it will be the smallest of larger range
			medians.emplace_back(min_heap.top());
		}
	}
	
	return medians;
}

// overloading << for directly viewing the vector elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a << ", ";
	cout << endl;
}

int main() {
	string str = {"1,0,3,5,2,0,1"};
	istringstream ss(str);

	cout << showLiveMedian(&ss);
	return 0;
}
