/*
    Problem:
        Given an array where each entry stores the max steps that can be taken
        from there, find if we begin from the first index, if it possible to
        reach the last index.
    Input: int array
    Output: bool
    
    Solution:
        Starting from the first index we keep track of farthest index till which
        we can go, after the traversal is done if the farthest that we can go is smaller 
        than the last index, then cannot be reached.
        TC: O(n)
        SC: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// finds whether the last index can be reached starting from the 
// first index  
bool canEndBeReached(vector<int>& arr) {
    // for tracking the farthest index that till which can be jumped
    int farthest_index = 0;
    for(int i = 0; i <= farthest_index && i < arr.size(); i++) {
        farthest_index = max(farthest_index, arr[i] + i);
    }

    return farthest_index >= arr.size() - 1;
}

ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr) 
        cout << a << " ";
    cout << endl;
}

int main(){
    vector<int> arr = {1,3,0,0,2,0,1};

    cout << canEndBeReached(arr);
    return 0;
}
