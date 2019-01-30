/*
	Given an array of strings and a set of string keywords. Find the smallest subarray which contains the keywords.

	Input: array of strings
	Output: range indices of subarray

	Solution:

		We use two indices for keeping track of start and end index. We use the hash table for which uses the keywords
		as keys and count as their value. Now initially both start and end indices are 0, we start moving the 
		right index till all the keywords gets covered. Once all the keywords are covered, we try to move the left index so as
		to make the subarray smaller. If on moving the left index, if the coverage of the keywords is not possible then we
		move the right index till again all the keywords can be covered. While doing all this we keep track of start and end indices
		such that min|end - start|.

		TC: O(n)
		SC: O(m), m: no. of keywords
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the index of smallest subarray which contains the given set of keywords
pair<int, int> smallestSubarrayWithKeywords(vector<string>& arr, 
										unordered_set<string>& keywords) {
	// first term contains starting index and second term contains ending index 
	pair<int, int> keywords_subarray = {-1, -1};

	// for keeping count of keywords, it will be 1 for keywords since we are using set for keywords
	unordered_map<string, int> keyword_freq;
	// for keeping track of total keywords to cover
	int num_keywords_cover = keywords.size();

	for(const auto& keyword: keywords) {
		++keyword_freq[keyword];
	}

	// The entire traversal happens in two phases:
	// 1. We traverse using right index till all the keywords are covered, which is the primary obj.
	// 2. We go for secondary objective of finding the smallest subarray, so we try to move the left index 
	// 	  untill the keywords are still being covered.
	for(int left = 0, right = 0; right < arr.size(); right++) {
		// if the current word is a keyword 
		// we also check if the current keyword is already there in excess or not
		// if count for current keyword is negative that means required number of current keywords have 
		// already been scanned and this is just extra, so we don't derement out total keywords to cover count
		if(keywords.count(arr[right]) && --keyword_freq[arr[right]] >= 0) {
			// once a keyword is found, we can decrement 1 from total keywords to cover
			--num_keywords_cover;
		}

		// check if all the keywords have been covered or not, if they have been covered then just
		// just move the left index till again they are not covered
		while(num_keywords_cover == 0) {
			// check if the current sub array is min
			if((keywords_subarray.first == -1 && keywords_subarray.second == -1 ) || 
					abs(right - left) < abs(keywords_subarray.second - keywords_subarray.first)) {
				
				keywords_subarray.first = left;
				keywords_subarray.second = right;
			}
			// check if the current keyword is extra or not
			if(keywords.count(arr[left]) && ++keyword_freq[arr[left]] > 0) {
				++num_keywords_cover;
			}
			// move left index
			++left;
		}
	}

	return keywords_subarray;
}


int main() {
	vector<string> arr = {"I", "apple", "kiwi", "banana", "was", "apple", "orange", "apple", "banana", "new",
						"new", "new"};
	unordered_set<string> keywords = {"banana", "apple"};
	
	pair<int, int> subarray_idx = smallestSubarrayWithKeywords(arr, keywords);
	cout << "Start: " << subarray_idx.first << ", Second: " << subarray_idx.second << endl;
	
	return 0;
}  
