/*
    Print the values of a 2d matrix in spiral form

    Input: 2 array 
    Output: output elements

    Solution:
        Use pointers for keeping track of col and row end points.
        Print and decrement accordingly
        TC: O(nm), n: no. of rows and m: no. of columns
        SC: O(nm)
*/

#include <iostream>
#include <vector>
using namespace std;

// prints 2d grid in spiral form
void printSpiral(vector<vector<int>>& grid) {
    // row and column start and end indices
    int row_s = 0, row_e = grid.size() - 1;
    int col_s = 0, col_e = grid[0].size() - 1;

    while(row_s <= row_e && col_s <= col_e) {
        // print the top side
        for(int i = col_s; i <= col_e; i++)
            cout << grid[row_s][i] << " ";
        ++row_s;
        
        // print the right side
        for(int i = row_s; i <= row_e; i++)
            cout << grid[i][col_e] << " ";
        --col_e;
        
        // print the bottom side
        for(int i = col_e; i >= col_s; i--)
            cout << grid[row_e][i] << " ";
        --row_e;
        
        // print the left side
        for(int i = row_e; i >=  row_s; i--)
            cout << grid[i][col_s] << " ";
    	++col_s;
    }
}

int main() {
    vector<vector<int>> matrix = {  {1, 2, 3, 33},
                                    {4, 5, 6, 66},
                                    {7, 8, 9, 99},
                                    {10, 11, 12, 122}
                                   // {13, 14, 15}
                                };
        printSpiral(matrix);
    return 0;
}
