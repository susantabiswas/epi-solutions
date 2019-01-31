/*
	Given an array of int, find the length of longest subarray such that for any two elements lying in the
	subarray, all the numbers between them are also covered in the subarray. It is not necessary to have 
	them appear sequentially in original array. eg: 1,2,8,3: <1,2,3> 

	Input: array of int
	Output: int 

	Solution:
		We use a hash table for keeping track of numbers not assigned to a subarray.
		Initially the hash table is filled with all distinct numbers.
		The pick one number from the table, and start checking for numbers in +1, -1 directions.
		If the numbers are available in hash table then we remove them from the hash table
		so that for selection of a number for next subarray we dont go thorugh all these numbers.
		
		TC: O(n)
		SC: O(m), m: no. of distinct numbers
*/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the length of the longest interval length such that it contains all the numbers
// which belongs there
int longestContainedInterval(const vector<int>& arr) {
	// for keeping track of available numbers, ini contains all numbers
	unordered_set<int> avail_nums(arr.begin(), arr.end());
	// upper and lower interval bounds
	int upper = 0;	 
	int lower = 0;
	int longest_interval = 0;

	while(!avail_nums.empty()) {
		int num = *avail_nums.begin();
		// remove the number
		avail_nums.erase(num);

		lower = num - 1;
		// now find all numbers which are smaller than it
		while(avail_nums.count(lower)) {
			// remove from available set
			avail_nums.erase(lower);
			--lower;
		}
		// find all numbers greater than it
		upper = num + 1;
		while(avail_nums.count(upper)) {
			avail_nums.erase(upper);
			++upper;
		}

		// update longest interval if longer
		longest_interval = max(longest_interval, upper - lower - 1);
	}

	return longest_interval;
}

int main() {
	vector<int> arr = {10, 5, 3, 11, 6, 100, 4};
	cout << longestContainedInterval(arr);
	return 0;
}
