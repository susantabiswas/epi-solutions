/*
	Given an input stream of strings and a set of string keywords. Find the smallest subarray which contains the keywords sequentially.

	Input: array of strings
	Output: range indices of subarray

	Solution:

		The keywords can be indexed from 0. Here we use a vector which stores the length of the smallest subarray covering all 
		the keywords till the lastest occurrence of that keyword. Also there is another vector which stores the latest occurrence of 
		keywords and also a hash table whose key is keyword and value is 0 based index for that keyword.

		hash_table<keyword, index_value>--->index_value used for mapping vector_length and vector_occurrence

		Initially all the length values are INF and to ensure that we have found the keywords sequentially, we update the
		length of each keyword using the value from previous keyword, if the keyword has been covered then only the 
		current keyword can be covered. 

		TC: O(n)
		SC: O(m), m: no. of keywords
*/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the index of smallest subarray which contains the given set of keywords sequentially
pair<int, int> smallestSequentialSubarrayWithKeywords(vector<int>& arr, 
										const vector<string>& keywords) {
	// for storing the keyword with their index
	unordered_map<string, int> keyword_idx; 
	// for stroing the latest index occurrence
	vector<int> latest_occurrence(keywords.size(), -1);	
	// for storing the smallest subarray length covering keywords till index 'i' for each index 'i'  
	vector<int> smallest_subarray_length(keywords.size(), numeric_limits<int>::max()); 
	
	// global min length of subarray
	int global_smallest_subarray_length = numeric_limits<int>::max();
	pair<int, int> keywords_subarray = {-1, -1};

	// first set the index values for each keyword
	for(int i = 0; i < keywords.size(); i++) {
		keyword_idx[keywords[i]] = i;
	}

	for(int i = 0; i < arr.size(); i++) {
		// check if the current word is a keyword
		auto it = keyword_idx.find(arr[i]);

		if(it != keyword_idx.end()) {
			// get the index mapping for the current keyword
			int idx = it->second;

			// if it is the starting keyword, then set its length as 1
			if(idx == 0) {
				smallest_subarray_length[idx] = 1;
			} 
			else if(smallest_subarray_length[idx] != numeric_limits<int>::max()) {	// if the keywords before this have been covered
				// update the shortest length for current keyword
				smallest_subarray_length[idx] = smallest_subarray_length[idx-1] +
												i - latest_occurrence[idx-1];
			}
			else if (idx == keyword.size() - 1) {	// if it is the last keyword, check if subarray length is global min or not
				if(smallest_subarray_length[idx] < global_smallest_subarray_length) {
					global_smallest_subarray_length = smallest_subarray_length[idx];
					keywords_subarray = {latest_occurrence[0], idx};
				}
			}

			// set the lastest occurrence
			lastest_occurrence[idx] = i;
		}
	}	

	return keywords_subarray;
}

int main() {
	vector<string> arr = {"I", "apple", "kiwi", "banana", "was", "apple", "orange", "apple", "banana", "new",
						"new", "new"};
	vector<string> keywords = {"banana", "apple"};
	
	pair<int, int> subarray_idx = smallestSequentialSubarrayWithKeywords(arr, keywords);
	cout << "Start: " << subarray_idx.first << ", Second: " << subarray_idx.second << endl;
	return 0;
}
