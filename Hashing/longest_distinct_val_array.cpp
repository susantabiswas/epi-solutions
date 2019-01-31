/*
	Given an array of strings, find the length of longest subarray which has distinct elements.
	Input: array of strings
	Output: int 

	Solution:
		We keep track of starting index of subarray which has all distinct elements and longest length value.

		For some index 'i', if we know the length of longest subarray with distinct elements till that index, then
		for the next index two things can happen:
		1. Either that is a duplicate:
				Now if the start index dup free subarray needs to change, since current element is a duplicate and
				the longest subarray cannot continue. So to again make the subarray distinct we make the start index
				the next element of last known index of current duplicate

				update longest value if current subarray is longer
		2. Another distinct element
				continue to next element

		Update the recent location of current word in hash table

		TC: O(n)
		SC: O(m), m: no. of keywords
*/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the length of the longest subarray with distinct values
int longestDistinctValueSubarray(const vector<string>& arr) {
	// for storing the most recent index for each word
	unordered_map<string, int> recent_idx;
	// for keeping track of start index of duplicate free subarray
	int start_dup_free = 0;
	// for keeping track of longest length
	int longest_len = 0;
	
	// traverse through all words 
	for(int i = 0; i < arr.size(); i++) {
		// check if the current word has already been seen or not
		auto it = recent_idx.emplace(arr[i], i);

		// if the current is a duplicate 
		if(it.second == false) {
			// if the duplicate appears after start index of dup free subarray
			if(it.first->second >= start_dup_free) {
				// check if the current length is greater
				longest_len = max(longest_len, i - start_dup_free);
				// update the start index to next index of last seen index of current element
				start_dup_free = it.first->second + 1;
			}
		// set the recent index of current element
		recent_idx[arr[i]] = i;
		}
	}
	// since length gets updated only when duplicate is found, so we do it 
	// in the end to account for cases when last seen element were only distinct elements
	int l = arr.size() - start_dup_free;
	longest_len = max(longest_len, l);
	return longest_len; 
}

int main() {
	vector<string> arr = {"I", "apple", "kiwi", "banana", "was", "apple", "orange", "apple", "banana", "new",
						"new", "new"};
	
	
	int len = longestDistinctValueSubarray(arr);
	cout << "Length: " << len << endl;
	return 0;
}
