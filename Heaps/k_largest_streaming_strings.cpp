/* 
	There is a stream of string words coming, find the 'k' largest strings.
	
	Input: streaming strings
	Output: k largest strings
	
	Solution:
		We use a min-heap of size 'k'. We start pushing strings in it. The heap property is 
		based on length of string. Since it is a min-heap it will always have the shortest 
		string at top. We push the current string in it and if heap size > k, pop the smallest.

		TC: O(nlogk + nL), O(logk) for insertion and deletion and we do it 'n' no. of times. 
  			Each time string is copied so it takes O(L), L = Longest string
		SC: O(kL)
	*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

// finds the k largest strings
vector<string> findKLargestStrings(istringstream* ss, int k) {
	vector<string> k_largest;
	
	// make a min-heap
	/*
		The comparison for priority queue is not very explanatory since for
		min we are using >=. The reason is based on this ordering it will have the
		elements ordered and the top element will be the last element in this ordering. So
		for getting min element, we give the comp such that the elements are ordered in
		non-increasing order and last will be smallest.
	*/
	priority_queue<string, vector<string>, function<bool(string, string)>>
		min_heap([](const string& a, const string& b)->bool{
			return a.size() >= b.size();
		});

	// go through each string
	string str;
	while(*ss >> str) {
		// push the string in min-heap
		min_heap.emplace(str);
		if(min_heap.size() > k) {
			min_heap.pop();
		}
	}
	
	while(!min_heap.empty()) {
		k_largest.emplace_back(min_heap.top());
		min_heap.pop();
	}
	
	return k_largest;	
}

// overloading << for directly viewing the array elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a << " ";
	cout << endl;
}

int main() {
	string txt = "apple banana cake lemon apple toffee";
	istringstream ss(txt);
	int k = 3;
	
	cout << findKLargestStrings(&ss, k);
	return 0;
}
