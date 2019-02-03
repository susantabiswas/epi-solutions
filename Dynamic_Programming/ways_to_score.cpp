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
#include <unordered_map>
using namespace std;

// finds the combination in which a score can be made
int combinationOfScore(int score, vector<int>& possible_scores) {
    
}

int main() {
    int score = 12;
    vector<int> possible_scores = {2, 3, 7};
    cout << combinationOfScore(score, possible_scores);
    return 0;
}
