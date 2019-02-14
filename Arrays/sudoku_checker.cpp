/*
    Implement a sudoku checker. The grid can be partially filled only, vacant positions are
    denoted by 0.                                                                                                                                                                                                                                                                                                                                                        ku checker

    Input: 2 array 
    Output: bool

    Solution:
        The constraints for a sudoku:
        Entries should be [1, 9]
        There should be unique entries in each row, column and in each smaller grid  
        TC: O(nm), n: no. of rows and m: no. of columns
        SC: O(nm)
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// checks if duplicates are there in region defined by row start and row end,
// column start and columnn end
bool isValidRegion(vector<vector<int>>& grid, int row_s, int row_e,
                            int col_s, int col_e) {
    // for keeping track of visited numbers, where ith index tracks num 'i'
    vector<bool> nums(9, false);

    // go through the region while marking the numbers
    for(int i = row_s; i < row_e; i++) {
        for(int j = col_s; j < col_e; j++) {
            // if the location is not vacanat, then mark that number as visited
            if(grid[i][j] != 0) {
                if(nums[grid[i][j]])
                    return false;
                else
                    nums[grid[i][j]] = true;
            }
        }
    }
    return true;
} 


// checks if the given sudoku is valid or not 
bool isSudokuValid(vector<vector<int>>& grid) {
    const int N = grid.size();  // no. of rows
    const int M = grid[0].size(); // no. of columns

    // check row constraint
    for(int i = 0; i < N; i++) {
        if(!isValidRegion(grid, i, i + 1, 0, M))
            return false;
    }

    // check column constraints
    for(int i = 0; i < M; i++) {
        if(!isValidRegion(grid, 0, N, i, i + 1))
            return false;
    }

    int num_regions = sqrt(N); // no. of smaller grid inside the sudoku board
    // check smaller grid constraints
    for(int i = 0; i < num_regions; i++) {
        if(!isValidRegion(grid, i * num_regions, i * num_regions + num_regions,
                                i * num_regions, i * num_regions + num_regions))
            return false;
    }
    
    return true;
}

int main() {
    vector<vector<int>> grid = { // to do 9 X 9 data matrix
                                };
    cout << isSudokuValid(grid);
    return 0;
}					
