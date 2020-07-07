/*
    Word segmentation problem:
        Given a dictionary of words and a string. Check if the string can be 
        decomposed in terms of dictionary words.
    
        Input: set of strings, single string
        Output: vector of decomposed words
    Solution:
        We use a 1d array storing the length of the word ending at that index. Initially every entry is -1.
        We start traversal through the given string and for each i < n,
        we check if the word formed by (0, i) is in the dict or not. 
        If it is there, then goto next index
        else:
            go back and find the last indices where a dict word ended, from there
            start checking if a word can be formed by (k, i), k < i.
            We can do one optimisation here, instead of going back all the way back to index 0, 
            we can find the length of longest word and if the length is W.
            Then we start searching from W indices back only, using this approach makes O(W^2)     
        TC: O(n^3) normal way, O(nW^2) if longest word length is found in advance
        SC: O(n), n: length of string 
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the longest length of dict word
int longestDictWordLength(unordered_set<string>& dict) {
	int max_length = 0;
	for(const auto& word: dict) {
		int len = word.size();
		max_length = max(max_length, len);
	}
	return max_length;
}

// checks if a string can be decomposed in terms of given dictionary words
vector<string> canStringBeDecomposed(string str, unordered_set<string>& dict) {
    // each entry stores the length of the word ending at that index starting (0, i)
    vector<int> word_ending_length(str.size(), -1);
	
	// get the length of longest word
	int longest_word_len = longestDictWordLength(dict);
	
   // traverse through the string and keep checking if the subtring is a dict string 
   for(int i = 0; i < str.size(); i++) {
       // if the current substring exists in dict
       if(dict.find(str.substr(0, i + 1)) != dict.end()) {
           word_ending_length[i] = i + 1;
       }

       // now if there is no substring(0, i) that is a valid word, then
       // check if there is any starting point after 0 from 
       // where a valid word can be formed
       if(word_ending_length[i] == -1) {
	      
           /*for(int j = 0; j < i; j++) {    // TC: O(n^2)
               // if a word is found
               if(word_ending_length[j] != -1) {
                   if(dict.find(str.substr(j+1, i - j)) != dict.end()) {
                       word_ending_length[i] = i - j;
                       break;
                   }
               }
            }*/
            // TC: O(W^2), since this loop run for W length
	    // if there really is a word, then at max it can be longest_word_len
	    // back from 'i'
            int j = i - longest_word_len >= 0 ? i - longest_word_len : 0;
            for(; j < i; j++) {
               // if a word is found
               if(word_ending_length[j] != -1) {
                   if(dict.find(str.substr(j+1, i - j)) != dict.end()) {
                       word_ending_length[i] = i - j;
                       break;
                   }
               }
            }
       }
    }

    // if the last entry in word_ending_length is -1, that means 
    // no word was found till last index, so the string is not decomposable
    if(word_ending_length[str.size() - 1] == -1) 
        return vector<string>{};

    // get the individual words from string
    vector<string> words;
    int word_idx = str.size() - 1;
    while(word_idx >= 0) {
        string word = str.substr(word_idx + 1 - word_ending_length[word_idx], word_ending_length[word_idx]);
        words.emplace_back(word);
        word_idx = word_idx - word_ending_length[word_idx];
    }

    return words;
}

ostream& operator<<(ostream& out, vector<string> arr) {
	for(const auto& a: arr)
		cout << a <<" ";
	cout << endl;
}

int main() {
    unordered_set<string> dict = {"mobile","samsung","sam","sung", 
                            "man","mango","icecream","and", 
                             "go","i","like","ice","cream", "jam", 
                             "painting", "paint","inga","park", "lake"};
    string str = "ilikepaintinga";

    cout << canStringBeDecomposed(str, dict);    
    return 0;
}
