/*
	String decomposition: Given a sentence string and a set of words. Find whether the concatenation of words in any order is there 
	inside the sentence string or not. Return the starting index. All the words in words vector are of same length.

	Input: sentence string and vector of word string
	Output: int

	Solution:
		For each index in sentence, we send the the sentence starting that point and vector of words to check:

		Checking func:
			The words are of same length so, we take the first word formed from sentence by taking the first 'm'
			characters and check if it is a word or not, then we continue for the remaining words by taking the
			next 'm' characters. If all the words gets finished, then it is possible else return false

		TC: O(n)
		SC: O(m), 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// checks if 
// checks if the given sentence contains the concatenation of words in any order
// returns the starting index if so
vector<int> stringDecompositionPossible(string& sentence, vector<string>& words) {
	int start = -1;
	vector<int> result;
	// store the frequency of each word
	unordered_map<string, int> word_freq;
	for(const auto& word: words) {
		++word_freq[word];
	}

	int word_length = words.front().size();
	int num_words = words.size();

	for(int i = 0; i + word_length * num_words < sentence.size(); i++) {
		// check if sentence starting 'i' contains the words or not
		if(doesSentenceContainWords(sentence, i, word_freq, words))
			result.emplace(i);
	}

	return start;
}

int main() {
	string sentence = "";
	vector<string> words = {};

	vector<int> res = stringDecompositionPossible(sentence, words);
	for(const auto& r: res) 
		cout << r << " ";
	return 0;
}
 
