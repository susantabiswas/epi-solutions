/*
    Problem:
        Given a NxN board, the aim is to place N queens on the board such that
        no two queens can attack each other. A queen attacks another queen if the queen is in the
        same row, column or diagonal.

        TC: O(n!)


    Input:
        N: dimension of board

    Output:
        All possible 2D matrices depicting the placement
*/

#include<iostream>
#include<vector>
#include<memory>
#include<cmath>
using namespace std;


// prints the position of queens on the board
void displayPlacement(int n, vector<vector<int>>& placement){
    vector<int>::iterator it;
    for(int i = 0; i< placement.size(); i++){
        for(it = placement[i].begin(); it!=placement[i].end(); it++){
            for(int j = 0; j<n; j++){
                if(j == *it)
                    cout << "1" << " ";
                else
                    cout << "0" << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}

// checks whether the current queen placement is valid or not
bool isPositionValid(const vector<int>& col_placement){
    // find the total no. of row queens placed so far
    int last_row = col_placement.size() - 1;

    // for storing the position difference
    int pos_diff = 0;

    // Now all the previous queens have a valid position except for the
    // last queen, validity of whose position is not known now
    // So we check if any previous the current column placement of queen
    // coincides with any of the columns of previous rows and diagonals
    for(int i = 0; i < last_row; i++){
        pos_diff = abs(col_placement[i] - col_placement[last_row]);
        // if the column conflict is there then the pos_diff = 0
        // if the diagonal conflict is there then the pos_diff and (last_row-i) will
        // be the same, since the board is symmetric and because of which the horizontal col index diff
        // and vertical row index diff becomes the same
        if(pos_diff == 0 || pos_diff == (last_row - i)){
            return false;
        }
    }
    return true;
}

// for placing the N queens
/*
    Uses backtracking for finding the possible placement positions.

*/
void placeNQueens(int curr_row, int n, vector<int>& col_placement,
                                vector< vector<int> >& placement){
    // when the current row index equals total rows that means
    // that all the queens have been placed successfully, so this placement
    // is valid
    if(curr_row == n){
        // add the valid placement info
        placement.emplace_back(col_placement);
    }
    else{
        // try all possible column combinations
        for(int i = 0; i < n; i++){
            // try placing the queen at the current column 'i' for curr_row
            col_placement.emplace_back(i);
            //check if the positon of the queen is valid or not
            if(isPositionValid(col_placement)){
                placeNQueens(curr_row+1, n, col_placement, placement);
            }
            col_placement.pop_back();

        }
    }

}

// driver function for N queens
void placeNQueensDriver(int n){
    // for storing the placement information for all possible combinations
    vector<vector<int>> placement;
    vector<int> col_placement;
    placeNQueens(0, n, col_placement, placement);
    displayPlacement(n, placement);
}

int main(){
    placeNQueensDriver(4);
    return 0;
}
