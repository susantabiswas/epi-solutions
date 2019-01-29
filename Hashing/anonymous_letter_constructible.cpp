/*
	Given two sources of chars, s1 and s2. Check if s1 can be formed from s2 
	Input: string, string
	Output: bool
	
	Solution:
		Create a hash table with chars of s1 and for values have the frequncy of each char.
		Then do a traversal of s2 and for each char decrement count in hash table for that char,
		if the freq becomes zero, remove that char. If the hash table becomes empty then return true else 
		if after traversal the hash table is not empty return false.

		TC: O(n + m), n:chars in s1, m: chars in s2 
		SC: O(m), m: unique chars in s1 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// checks if s1 can be made using s2
bool canS2CreateS1(const string& s1, const string& s2) {
	// for taking the freq count of s1
	unordered_map<char, int> char_freq;
	
	// store freq for chars of s1
	for(const char& c: s1)
		++char_freq[c];

	// check if s1 can be made from s2
	for(const char& c: s2) {
		// decrement the count of current char if its there in s1
		if(char_freq.find(c) != char_freq.end()){
			--char_freq[c];
			// check if the count has become zero or not
			if(char_freq[c] == 0){
				// remove the char from hash table
				char_freq.erase(c);
			}
			// check if the hash table is empty or not
			if(char_freq.empty())
				return true;
		}
	}

	return char_freq.empty() ? true : false;
}

int main() {
	string s1 = "aadd";
	string s2 = "afad";
	
	cout << canS2CreateS1(s1, s2);
	return 0;
}
