/*	
	Given an int score and a list of scores that can be scored by 
    different moves. Find the total number of ways in which the score 
    can be achieved. Possible scores for moves are 2, 3 and 7.

	Input: int, int array
	Output: int

	Solution:
	    For a given score, we can either include the current move score or
        ignore it.
        If the current move score is greater than the final score, we try
        the smaller scores.
        TC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

int waysToScoreTabulationHelper(int score, vector<int>& play_scores, 
                vector<vector<int>>& cache) {
    // if the score has been reached
    if(score == 0)
        return 1;
    
    // if the cached value is there
    if(cache[score] != 0)
        return cache[score];

    for(int i = 0; i < play_scores.size() && play_scores[i] < score; i++) {
        cache[score] += waysToScoreTabulationHelper(score - play_scores[i],
                                                play_scores, cache);
    }

    return cache[score];
}

int waysToScoreTabulation(int score, vector<int> play_scores) {
    // each ith entry stores the no. of ways in which that can be
    // acheived 
    vector<int< cache(score + 1, 0);
    return waysToScoreTabulationHelper(score, play_scores, cache);
}

// helper function for the memoization functionality
int waysToScoreMemoizationHelper(int score, int n, vector<int>& play_scores, 
                            vector<vector<int>>& cache) {
    // when the score has been reached
    if(score == 0)
        return 1;
    
    // if the current play score is larger, then try the next one
    if(play_scores[n - 1] > score)
        return cache[score][n-1] = waysToScoreMemoizationHelper(score, n-1, play_scores, cache);
    
    if(cache[score][n-1] == 0) {
        // try all possible play scores till n
        for(int i = 0, i < n; i++)
            cache[score][n-1] += waysToScoreMemoizationHelper(score - play_scores[i], i + 1, play_scores, cache);
    }
    return cache[score][n-1];
}

// using memoization
// finds the number of ways in which a score can be acheived
int waysToScoreMemoization(int score, const vector<int>& play_scores) {
    // each entry 'i', 'j' stores the number of ways in which
    // that score can be acheived when play_scores till 'i' are allowed.
    vector<vector<int>> cache(play_scores.size(), vector<int>(scores + 1, 0));

    return waysToScoreMemoizationHelper(score, play_scores.size(), play_scores, cache);
}

int main() {
    const vector<int> play_scores = {};
    int score = ;
    cout << waysToScore(score, play_scores);
    return 0;
}
