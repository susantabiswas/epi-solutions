/*
    Given a int score and a scores for different moves/plays. Find the no. of ways in which that
    score can be acheived.

	Input: int, int
	Output: int
	
	Solution:
        Very similar to climbing stairs problem

        TC: O(sn), s: score and n: no. of play scores

*/

#include <iostream>
#include <vector>
using namespace std;

/*int waysToScoreMemHelper(int score, vector<int>& play_scores, 
                vector<int>& cache) {
    // when the score is reached
    if(score == 0)
        return 1;
    
    // when the result is not cached, compute
    if(cache[score] == 0) {
        // try all play scores which can help achieve current score
        for(int i = 0; i < play_scores.size() && score - play_scores[i] >= 0; i++) {
            cache[score] += waysToScoreMemHelper(score - play_scores[i], play_scores, cache);
        }
    }
    return cache[score];
}

int waysToScoreMem(int score, vector<int> play_scores) {
    // each ith entry stores the no. of ways in which that can be
    // acheived 
    vector<int> cache(score + 1, 0);
    return waysToScoreMemHelper(score, play_scores, cache);
}*/


// finds the no. of ways a score can be acheived
int waysToScore(int final_score, const vector<int>& play_scores) {
	// each entry (i, j) stores the no. of ways in which score 'j' can
	// be acheived if playscores till 'i' in play scores vector are allowed
	vector<vector<int>> score_cmb(play_scores.size(), vector<int>(final_score + 1, 0));
	
	// we start from bottom and go upto the top 
	for(int i = 0; i < play_scores.size(); i++) {
		// score of 0 can be acheived in 1 way by every play score
		score_cmb[i][0] = 1;
		
		// find the ways for building 'j' score 
		for(int j = 1; j <= final_score; j++) {
			// for getting current score, we can either
			// include the current play score or 
			// exclude the current play score
			int exclude_current_score = i >= 1 ? score_cmb[i - 1][j] : 0;
			int include_current_score = play_scores[i] <= j ? score_cmb[i][j - play_scores[i]] : 0;
			
			score_cmb[i][j] = include_current_score + exclude_current_score;
		}
	}
	return score_cmb[play_scores.size() - 1][final_score];
}

int main() {
    const vector<int> play_scores = {1,2,3};
    int score = 5;
    cout << waysToScore(score, play_scores);
    
    return 0;
}
