/*
	Given a string, find whether it can be palindromic if the characters are arranged accordingly.
	Input: string
	Output: bool
	
	Solution:
		A word is palindromic if the each character has a pair if the string length is even, else
		all character except for one should have a pair.
		So we make a hash table with character as key and the frequency as value. Then once the
		traversal is done, check if:
		String length even:
			all the frequencies are even
		String length odd:
			all the frequencies are even and one char has an odd freq.

		TC: O(n), n: no. of chars
		SC: O(m), m: unique characters
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// checks if the word can be made palindromic or not
bool canBeMadePalindromic(string& word){
	unordered_map<char, int> char_count;

	// do traversal of the entire string
	for(const char& c: word) {
		++char_count[c];
	}
	
	int odd_freq = 0;
	
	// check for the frequencies
	for(const auto& freq: char_count){
		// if the char is odd and already an odd char is there 
		if(freq.second % 2 != 0 && ++odd_freq > 1)
			return false;
	}
	
	return true;
}

int main() {
	string word = "aabbcd";
	
	cout << canBeMadePalindromic(word);
	return 0;
}
