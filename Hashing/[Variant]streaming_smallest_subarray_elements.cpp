/*
	Given an input stream of strings and a set of string keywords. Find the smallest subarray which contains the keywords.

	Input: array of strings
	Output: range indices of subarray

	Solution:

		Since the input is streaming we use a Doubly linked list for stroring the index of keywords. Everytime a keyword
		is seen we add its index to the back of the list, incase it was already seen once we remove that node and add the
		new recent index as the last node. 
		The first node of the list is the most earlier seen keyword, for each new input streamed word, we compute the 
		diff between first node index and the current index, if the subarray length is lesser than the current length and 
		all the keywords have been covered, update the subarray index.

		TC: O(n)
		SC: O(m), m: no. of keywords
*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the index of smallest subarray which contains the given set of keywords
pair<int, int> smallestStreamedSubarrayWithKeywords(istringstream* stream_in, 
										unordered_set<string>& keywords) {
	// first term contains starting index and second term contains ending index 
	pair<int, int> keywords_subarray = {-1, -1};

	// for keeping track of last seen index of keywords
	list<int> idx;
	// for keeping count of keywords, it will be 1 for keywords since we are using set for keywords
	unordered_map<string, list<int>::iterator> keyword_idx;
	// for keeping track of total keywords to cover
	int num_keywords_cover = keywords.size();

	// set the location of keywords index initially not set
	for(const auto& keyword: keywords) {
		keyword_idx.emplace(keyword, idx.end());
	}

	// current streamed word index
	int curr = 0;
	string s;	

	while(stream_in >> s) {
		// check if the keyword exists
		auto it = keyword_idx.find(s);
		// update the last seen index of current keyword
		if(it != keyword_idx.end()) {
			if(it->second != keyword_idx.end())
				idx.erase(it->second);

			// add the latest index of keyword
			idx.emplace_back(curr);
			// update the iterator loc in hash table
			it->second = --idx.end();
		}
		
		// if all the keywords have been covered, then check if the current
		// subarray is smallest or not
		if(idx.size() == keywords.size()) {
			// check if the current sub array is min
			if((keywords_subarray.first == -1 && keywords_subarray.second == -1 ) || 
					(curr - idx.front()) < (keywords_subarray.second - keywords_subarray.first)) {
		
				keywords_subarray.first = idx.front();
				keywords_subarray.second = curr;
			}
		}

		// increament word index count
		++curr;
	}
	return keywords_subarray;
}

