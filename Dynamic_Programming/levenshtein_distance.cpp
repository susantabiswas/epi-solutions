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
using namespace std;

// helper for the finding the levenshtein distance using memoization
int minLevenshteinDistanceHelper(string a, int n, string b, int m,
                            vector<vector<int>>& cache) {
    // if string 'a' has finished, remaining chars of 'b' needs
    // to be inserted
    if(n == 0)
        return m;
    // if string 'b' has finsihed, then remaining 'a' chars needs
    // to deleted
    if(m == 0)
        return n;

    // if current chars of both the strings are same, then check the
    // next string
    if(a[n-1] == b[m-1])
        return cache[n-1][m-1] = minLevenshteinDistanceHelper(a, n-1, b, m-1, cache);

    if(cache[n-1][m-1] == -1) {
        cache[n-1][m-1] = 1 + min({ minLevenshteinDistanceHelper(a, n-1, b, m-1, cache), // substitution
                                    minLevenshteinDistanceHelper(a, n-1, b, m, cache),  // deletion
                                    minLevenshteinDistanceHelper(a, n, b, m-1, cache)  // insertion
        });
    }
    
    return cache[n - 1][m - 1];
}

// finds the min levenshtein distance between two strings 
// to convert first string to second
int minLevenshteinDistance(string a, string b) {
    // for caching the intermediate results
    // each entry 'i' and 'j' stores min levenshtein distance till that index
    vector<vector<int>> cache(a.size(), vector<int>(b.size(), -1));

    return minLevenshteinDistanceHelper(a, a.size(), b, b.size(), cache);
}


int main() {
    return 0;
}
