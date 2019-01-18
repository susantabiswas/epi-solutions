/*
	Given a sorted array of distinct integer elements.
	Find the an element whose value matches its index.
	
	Input: array of int
	Output: if present return index else -1
	
	Solution:
    
        We can do binary search with target element set as the middle array
        element. Then 
            if the middle element equals the index
                 then return
            else if middle element is greater than its index
                go left
            else if middle element is smaller than its index
                fo right
        
        TC: O(logn)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds an element whose value equals its index and returns its index
int findElementMatchingIndex(vector<int>& arr){
    int l = 0;
    int h = arr.size()-1;
    // for keeping track of middle index
    int mid = -1;

    while(l <= h){
        // find  the middel index
        mid = l + (h - l) / 2;

        if(arr[mid] == mid)
            return mid;
        else if(arr[mid] > mid){ // when the element is greater than its index
            h = mid - 1;
        }
        else if(arr[mid] < mid){ // when the element is smaller than its index
            l = mid + 1;
        }
    }

    return -1;
}

int main() {
    vector<int> arr = {-23, -1, 0, 3, 4, 5, 15, 16, 17, 123, 872, 9089};

    cout << findElementMatchingIndex(arr);
	return 0;
}
