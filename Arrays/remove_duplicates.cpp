/*
    Given an array of numbers, there are duplicates of multiple numbers, the array is sorted.
    Move all the duplicates to the right side of the array such that all the distinct numbers
    exist first in the array. Return the index till the last valid distinct entry or directly the
    distinct number vector

    Solution:
        Use two pointers for tracking the current number and the index where the numbers will be 
        written. We start with index 1, if the left of index is same, move only the current index.
        If the left is different then write current at write index and increment write index.
        TC: O(n)
        Sc: O(1)
*/

#include <iostream>
#include <vector>
using namespace std;

// remove duplicates
vector<int> removeDuplicates(vector<int> arr) {
	if(arr.empty())
		return vector<int>{};
		
    // index where the element will be saved/written
    int write_idx = 1;
    // current element index
    int curr_idx = 1;

    while(curr_idx < arr.size()) {
        // when the adjacent elements are different
        // write current element at writing index
        if(arr[curr_idx] != arr[curr_idx - 1]) {
            arr[write_idx] = arr[curr_idx];
            write_idx++;
        }
        ++curr_idx;
    }
    return vector<int>{arr.begin(), arr.begin() + write_idx};
}

ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr)
        cout << a << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {1, 1, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8};
    cout << removeDuplicates(arr);
    return 0;
}
