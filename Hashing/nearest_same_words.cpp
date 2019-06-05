/*
	Given an array of string, find the closest distance between the same words in the array

	Input: array of string
	Output: int

	Solution:
		Use hash table: key: string, value: index
		min_dist = INF
		For each entry in array:
			if present in hash table:
				dist = compute the distance of current index 'i' with hash table index of same string
				min_dist = min(min_dist, dist)
				update index in hash table
			else:
				add entry in hash table
						

		TC: O(n)
		SC: O(m), m: no. of distinct words
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

// finds the closest distance between same words
int findClosestWordsDistance(const vector<string>& arr) {
	int closest_dist = numeric_limits<int>::max();

	// stores the last known index of words
	unordered_map<string, int> last_word_idx;

	for(int i = 0; i < arr.size(); i++) {
		// if current word was there previously, compute the distance
		if(last_word_idx.find(arr[i]) != last_word_idx.end()) {
			closest_dist = min(closest_dist, i - last_word_idx[arr[i]]);
		}
		// update/insert the current word
		last_word_idx[arr[i]] = i;
	}
	return closest_dist;
}

int main() {
	vector<string> arr = {"I", "apple", "banana", "was", "apple", "orange", "apple", "banana"};	
	cout << findClosestWordsDistance(arr);
	return 0;
}
