/*
    Given an array of int, find the longest increasing subsequence.

    Input: int array
    Output: int

    Solution:
        We use a vector to store the longest length ending at each index for all elements.
        For each index, the longest increasing subsequence at that index is atleast 1,
        that is that element itself. From that index we we look at the previous
        indices and search for the longest length such that element is also smaller than
        current element, then we just check if 
            length[i] = max(length[j] + 1, length[i]) for j < i

        TC: O(n^2), j loop takes O(n)
        SC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

int longestIncreasingSubsequence(const vector<int>& arr) {
    int longest_length = 0;
	
    // for storing longest length ending at each index
    vector<int> longest_increasing_length(arr.size(), 1);
	// optional for storing the actual subarray
	vector<int> subarray(arr.size(), -1);
	int longest_length_ending_idx = 0;
	
    for(int i = 1; i < arr.size(); i++) {
        // check for the longest length in previous elements
        for(int j = 0; j < i; j++) {
            // update the longest length if necessary
            if(arr[j] <= arr[i]) {
        		if(longest_increasing_length[j] + 1 > longest_increasing_length[i]) {
        			longest_increasing_length[i] = longest_increasing_length[j] + 1;
            		subarray[i] = j;
        		}
            }
        }

		longest_length_ending_idx = longest_increasing_length[i] > longest_length ? i : 
									longest_length_ending_idx;
        longest_length = max(longest_length, longest_increasing_length[i]);
   }
    
    // it will print in reverse form
    while(longest_length_ending_idx != -1) {
    	cout << arr[longest_length_ending_idx] << " ";
    	longest_length_ending_idx = subarray[longest_length_ending_idx];
    }
    cout << endl;
    return longest_length;
}

int main() {
    vector<int> arr = {1, 8, 3, 11, 2, 10, 6, 14, 2, 9};
    cout << longestIncreasingSubsequence(arr);
    return 0;
}

