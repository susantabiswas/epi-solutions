/*
    Given 'n', find the first 'n' rows of pascal triangle.                                                                                                                                                                                                                                                                                                                                                      ku checker

    Input: int
    Output: n dim vector 

    Solution:
        In a pascal triangle for any row 'i':
            first and last elements are always 1, the elements between them are simply
            sum of the elements just above that in previous row.
        TC: O(n^2), n: no. of rows and m: no. of columns
        SC: O(n^2)
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// prints the pascal triangle
void printPascalTriangle(vector<vector<int>>& triangle) {
    int n = floor(triangle.back().size() / 2) + floor(triangle.back().size() / 2); 
    for(int i = 0; i < triangle.size(); i++) {
    	int k = 1;
        while(k++ <= n)
            cout << " ";
        --n;    
        for(int j = 0; j < triangle[i].size(); j++) {
            cout << triangle[i][j] << " "; 
        }
        cout << endl;
    }
}

// computes the rows of pascal triangle
void computePascalTriangle(int n) {
    vector<vector<int>> triangle(n);

    // starting element
    triangle[0].emplace_back(1);

    for(int i = 1; i < n; i++) {
        // first element is always 1
        triangle[i].emplace_back(1);
        
        // add the middle elements 
        for(int j = 1; j < i; j++) {
            triangle[i].emplace_back(triangle[i-1][j-1] + triangle[i-1][j]);
        }

        // last element is always 1
        triangle[i].emplace_back(1);
    }

    printPascalTriangle(triangle);
}

int main() {
    computePascalTriangle(5);
    return 0;
}
