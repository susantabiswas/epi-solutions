/* 
	Given two arrays signifying heights of players of two different teams. Check if the players from two teams 
	can stand in rows such that, player behind the player in front row should be taller than him. Each row has 
	players of same team only. 
	NOTE: Assume teams have same size
	Input: array of elements
	Output: bool

	Solution:
		Since the teams have same number of players, so if we have their heights sorted, then
		just checking if the tallest player from 1st team is taller than team 2 and doing this for all the 
		remaining players will do.

		TC: O(nlogn)
	*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// checks if the first team can be placed behind second team with constraints
bool canTeamBePlaced(vector<float>& team1, vector<float>& team2) {
	// sort the two teams
	sort(team1.begin(), team1.end());
	sort(team2.begin(), team2.end());

	for(int i = team1.size() - 1; i >= 0; i--) {
		// if team1's player is shorter than not possible
		if(team1[i] < team2[i])
			return false;
	}

	return true;
}

int main() {
	vector<float> team1 = {1.8, 1.8, 1.9, 2.1, 2.2};
	vector<float> team2 = {1.2, 2.1, 1.6, 1.8, 1.7};

	cout << (canTeamBePlaced(team1, team2) || canTeamBePlaced(team2, team1));
	return 0;
}
