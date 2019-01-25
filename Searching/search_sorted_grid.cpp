/*
    Given a 2D (m X n) grid where the row and column elements are non-decreasing. Find the target
	element in the grid.

	Input: 2D array of sorted int
	Output: bool (found/not found)
	
	Solution:
		The idea is to remove either a row/col in every iteration. If we can do that
		then this search can be done in O(m + n -1).
		Now the rows and cols both are sorted, so we can start with the smallest el of
		largest col or smallest el of largest row. The idea is to have either the max 
		value row with least value col or vice-versa, and based on the comparison with el
		we can remove either that row and col from search.

		Say we start with grid[m-1][0], then we compare it with target,
		if it is larger, then all the elements in col 0 are obviously lesser and we ignore
		that col, and make c=col+1. 
		if it is smaller, then all elements in that row will be larger than the target, so we
		remove the row from the search.

		TC: O(m + n - 1)
    
*/

#include <iostream>
#include <vector>
using namespace std;

// searches for an element in a 2d grid
bool searchInGrid(vector<vector<int>>& grid, int target){
	const int M = grid.size();
	const int N = grid[0].size();
	
	// starting value indices, we will be starting with
	// largest row with smallest column
	int row = M - 1;
	int col = 0;

	while(row >= 0 && col < N){
		// if the current element is equal to the target
		if(grid[row][col] == target)
			return true;
		else if(grid[row][col] > target)
			--row;
		else if(grid[row][col] < target)	
			++col;
	}
	return false;
}

int main() {
	vector< vector<int> > grid = {  {-1, 2, 4, 4, 6},
									{1, 5, 5, 9, 21},
									{7, 8, 9, 12, 25},
									{12, 13, 13, 34, 40}
								};

    cout << searchInGrid(grid, 812);
	return 0;
}
