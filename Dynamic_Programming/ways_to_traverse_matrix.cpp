/*
    Find the number of ways in which you can reach the right most bottom (n-1, m-1) 
    location of 2d array starting from 0,0. We can move only right and down.

    Input: array dimensions
    Output: int

    Solution:
        (n-1, m-1) can be reached only from its top or left location. And those
        locations can be reached only in a similar way. So for each location (i,j)
        we need to find the no. of ways to reach (i-1, j) and (i, j-1).

        L(i, j) = Top + Left
        Top : L(i-1, j) when i >= 1, 0 otherwise 
        Left : L(i, j-1) when j >= 1, 0 otherwise

        TC: O(nm), n: no. of rows and m: no. of columns
        SC: O(nm)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the no. of ways to reach bottom right
int waysToReachMatrixEndHelper(int n, int m, vector<vector<int>>& ways_to_reach) {
    // if the location has been reached
    if(n == 0 && m == 0)
        return 1;
    
    if(cache[n][m] == 0) {
        // check the no. of ways the left and top locations can be reached.
        // Also it is checked if it is the top row or first column or not

        // ways to reach the left location
        int reach_left = m == 0 ? 0 : waysToReachMatrixEndHelper(n, m-1, ways_to_reach);
        // ways to reach the top location
        int reach_top = n == 0 ? 0 : waysToReachMatrixEndHelper(n-1, m, ways_to_reach);

        cache[n][m] = reach_left + reach_top;
    }

    return cache[n][m];
}

int waysToReachMatrixEndHelper(int n, int m) {
    // each entry (i, j) stores the no. of ways that location can be 
    // from their left and top
    vector<vector<int>> ways_to_reach(n, vector<int>(m, 0));
    return waysToReachMatrixEndHelper(n - 1, m - 1, ways_to_reach); 
}

int main() {
    return 0;
}
