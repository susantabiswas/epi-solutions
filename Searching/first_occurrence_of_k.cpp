/*
	Given a sorted list array of elements and a target value.
	Find the first occurrence of that element in array.
	
	Input: arrayof int
	Output: index of first occurrence if present else -1
	
	Solution:
		We use binary search for this. Now there are two solutions:
		1. Do binary search once and if the element is there, from there we move left 
		   till the current element is different than target. The last index having target is 
		   the answer.
		   TC: O(n) + (logn)
		2. We can prune the array. Do binary search if the target is found, then we make
		   it the first occurrence and then again search for it in the left array subgroup 
		   since if target exists before current index it will in left side and not
		   in right side.
		   TC: O(logn)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the first occurrence of target element
int doFindFirstOccurrence(vector<int>& arr, int& target, int l, int h){
    
    // for keeping the middle index 
    int mid = -1;
    // for keeping track of first occurrence
    int first_occur = -1;

    while(l <= h){
        // find the middle index
        mid = l + (h - l) / 2;

        if(arr[mid] == target){
        	// make this as the first occurrence and 
        	// look for the rest
            first_occur = mid;
            // prune the right side completely
            h = mid - 1;
        }
        else if(arr[mid] < target){ // when the middle element is smaller, go right
            l = mid + 1;
        }
        else if(arr[mid] > target){ // when the middle element is larger, go left
            h = mid - 1;
        }
    }
    return first_occur;
}

// driver function for finding the first occurrence of target element
int findFirstOccurrence(vector<int>& arr, int target){
    // find the lower and upper limit
    int l = 0;
    int h = arr.size();

     return doFindFirstOccurrence(arr, target, l, h);
}

int main() {
    vector<int> arr = {-23, -1, 0, 2, 5, 6, 15, 15, 15, 123, 872, 9089};

    cout << findFirstOccurrence(arr, 15);
	return 0;
}
