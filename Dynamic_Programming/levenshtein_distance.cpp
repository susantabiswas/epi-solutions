/* 
    Levenshtein distance is the no. of edits to make a string 'a' convert to string 'b'.
    The edits can be: insert, delete and substitute chars.
    Find the min. no. of levenshtein distance for converting string 'a' to 'b'.

    Input: string, string
    Output: int
    
    Solution:
        There are three operations we are concerned with. So we start with the last character of both
        the strings.
        If the chars are same, go for the next char in both the strings
        if they are diff:
            we try for all three of the operations there.
            and take the min of all three
            F(n, m) = 1 + min {
                                insertion: F(n, m-1), insert the mth b char and check if the curr 'a' chars still matches the next b char or not
                                deletion: F(n-1, m), delete curr 'a' char and check if the next 'a' char still matches the last unmatching 'b' char
                                substitution: F(n-1, m-1), substitute the mth 'b' with 'n'th a char, and go for the next chars in both 'a' and 'b'
                            }

        TC: O(nm), n: string a length, m:string b length 
        SC: O(nm)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// helper for the finding the levenshtein distance using memoization
int minLevenshteinDistanceHelper(string a, int a_idx, string b, int b_idx,
                            vector<vector<int>>& cache) {
    // if string 'a' has finished, remaining chars of 'b' needs
    // to be inserted
    if(a_idx < 0 && b_idx >= 0)
        return b_idx + 1;
    // if string 'b' has finsihed, then remaining 'a' chars needs
    // to deleted
    if(b_idx < 0 && a_idx >= 0)
        return a_idx + 1;
	// if both are finished, then no edits are required
	if(a_idx < 0 && b_idx < 0)
		return 0;
		
    // if current chars of both the strings are same, then check the
    // next string
    if(a[a_idx] == b[b_idx])
        return cache[a_idx][b_idx] = minLevenshteinDistanceHelper(a, a_idx - 1, b, b_idx - 1, cache);

    if(cache[a_idx][b_idx] == 0) {
    	int substitute_op = minLevenshteinDistanceHelper(a, a_idx -1, b, b_idx -1, cache);
        int delete_op = minLevenshteinDistanceHelper(a, a_idx - 1, b, b_idx, cache);  
        int insert_op = minLevenshteinDistanceHelper(a, a_idx, b, b_idx - 1, cache); 
        
        cache[a_idx][b_idx] = 1 + min({substitute_op, delete_op, insert_op});
        
    }
    
    return cache[a_idx][b_idx];
}

// finds the min levenshtein distance between two strings 
// to convert first string to second
int minLevenshteinDistance(string a, string b) {
    // for caching the intermediate results
    // each entry 'i' and 'j' stores min levenshtein distance till that index
    vector<vector<int>> cache(a.size(), vector<int>(b.size(), 0));

    return minLevenshteinDistanceHelper(a, a.size() - 1, b, b.size() - 1, cache);
}


int main() {
	cout << minLevenshteinDistance("aab", "a");
    return 0;
}
