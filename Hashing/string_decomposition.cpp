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

		TC: O(Nnm), N: no. of chars in sentence, n: no. of words, m: length of each word
		SC: O(n) 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool doesSentenceContainWords(string& sentence, int& start, 
				unordered_map<string, int>& word_freq, vector<string>& words) {
	
	// to keep track of word repeatitions
	unordered_map<string, int> freq;
	int word_len = words.front().size();
	
	// we take word_len no. of chars from sentence and check if that word is any amongst
	// the given words
	for(int i = 0; i < words.size(); i++) {
		// extract word from sentence
		string curr_word = sentence.substr(start + i * word_len, word_len);

		// check if the word is there or not
		auto it = word_freq.find(curr_word);

		// if the word doesn't match means concated string not possible
		if(it == word_freq.end()) 
			return false;

		++freq[curr_word];
		// if a valid word appears more than required no. of times, that
		// means some other valid word won't be able to come, so false
		if(freq[curr_word] > word_freq[curr_word]) {
			return false;
		}
	}
	return true;
}

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
			result.emplace_back(i);
	}
	return result;
}

int main() {
	string sentence = "amanaplanacanal";
	vector<string> words = {"can", "apl", "ana"};

	vector<int> res = stringDecompositionPossible(sentence, words);
	for(const auto& r: res) 
		cout << r << " ";
	return 0;
}
 
