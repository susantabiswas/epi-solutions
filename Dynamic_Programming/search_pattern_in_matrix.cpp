/*
    Given a 1d array consisting of numbers and a 2d array. Check if the 
    matrix contains the array pattern. We can only move left, right, up and down 
    from a location every time.

    Input: 1d int array and 2d int array
    Output: bool

    Solution:
        If need to check from each location whether starting there will help us find the pattern or not.
            TC: O(nms) 
            Sc: O(nms)
            n: no. of rows, m: no. of cols, s: pattern string length
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <tuple>
using namespace std;

struct HashTupleElement {
    bool operator(const tuple<int, int, int>& el) const {
        // hash for the tuple element
        return hash<int>()(get<0>(el) ^ get<1>(el) * 1021 ^ get<2>(el) * 1048573);
    }
};

// checks if the pattern starting (i, j) contains the patterns
bool isPatternContainedStartingThis(vector<int>& pattern, int offset,
                                    int i, int j, vector<vector<int>>& matrix,
                                    unordered_set<tuple<int, int, int>, HashTupleElement>& grid_attempts) {
    // if the pattern is contained fully
    if(offset == pattern.size())
        return true;

    // if the current location is out of grid or if this has already been tried earlier
    if(i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() ||
        grid_attempts.find({i, j, offset}) != grid_attempts.end())
        return false;

    // if the current location matches the pattern starting
    if(matrix[i][j] == pattern[offset]) {
        // try all 4 directions 
        if( isPatternContainedStartingThis(pattern, offset + 1, i + 1, j, matrix, grid_attempts) ||
            isPatternContainedStartingThis(pattern, offset + 1, i - 1, j, matrix, grid_attempts) ||
            isPatternContainedStartingThis(pattern, offset + 1, i, j - 1, matrix, grid_attempts) ||
            isPatternContainedStartingThis(pattern, offset + 1, i, j + 1, matrix, grid_attempts) )
            return true;
    }
    // add the current attemp as failed
    grid_attempts.emplace({i, j, offset});
    return false;
}

// checks if a matrix contains a 1d pattern or not
bool isPatternContained(vector<int> pattern, vector<vector<int>> matrix) {
    // contains the failed attempts for a location and the 
    // pattern offset
    unordered_set<tuple<int, int, int>, HashTupleElement> grid_attempts;

    // we start the check from each location of matrix
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(isPatternContainedStartingThis(pattern, 0, i, j, matrix, grid_attempts))
                return true;
        }
    }
    return false;
}

int main() {

    return 0;
}
