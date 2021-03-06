/*
	KMP:
		Using brute force approach for string matching involves using every index for starting the search in case of
		failure. To avoid doing that each time we need to decide which index to start with we just check
		till which last character do we have matching results in pattern, then the next character is matched
		with current char of text.
		
	TC: O(n + m)
	SC: O(n), n: pattern length, m: string length
*/

#include <iostream>
#include <vector>
using namespace std;

// computes LPS
vector<int> computeLongestProperSuffix(string patt) {
	int i = 1, j = 0;
	vector<int> lps(patt.size(), 0);
	
	while(i < patt.size()) {
		// if the chars match
		if(patt[i] == patt[j]) {
			lps[i] = j + 1;
			++i, ++j;
		}
		else {
			if(j != 0) {
				j = lps[j-1];
			}
			else if(j == 0) {
				++i;
			}
		}
	}
	
	return lps;
}

// KMP algorithm: finds all the matching indices
vector<int> KMP(string str, string pattern) {
	if(str.size() < pattern.size() || pattern.size() <= 0 || str.size() <= 0)
		return vector<int>{};
		
	// compute the lps vector
	vector<int> lps = computeLongestProperSuffix(pattern);
	
	int i = 0, j = 0;
	vector<int> matches;
	
	while(i < str.size()) {
		if(pattern[j] == str[i]) {
			++i, ++j;
			// string match found
			if(j == pattern.size()) {
				matches.emplace_back(i - j);

				// decide the position of j to start matching
				if(j != 0) {
					j = lps[j-1];
				}
				else if(j == 0) {
					++i;
				}
			}
		}
		else {	// they don't match
			// decide the position of j to start matching
			if(j != 0) {
				j = lps[j-1];
			}
			else if(j == 0) {
				++i;
			}
		}
	}
	
	return matches;
}

int main() {
	string pattern = "abac";
	string str = "aabcabachabacsb";
	
	auto matches = KMP(str, pattern);
	for(const auto& a: matches)
		cout << a << " " ;
	return 0;
}

