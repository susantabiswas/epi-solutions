/*
    Given a cyclically sorted array of distinct integers. Find the smallest number.    
	
	Input: array of int
	Output: int
	
	Solution:
		We can use binary search for this. We start with left=0 and right=size()-1
		then:
			left = 0, right = arr.size()-1
			while(left < right):
				middle = find middle

				if middle el > right el:
					Means the smallest number will lie in [middle+1, right-1], all the
					el after right will be greater than right.
				else if middle el < right el:
					means smallest will lie between [right, middle-1], since all
					el after middle are greater than middle, hence can;t be smallest
			
			return left 

		NOTE: middle el != right since all are distinct, if non-distinct are allowed
			then it takes O(n), as we can't decide where to go when middle=right
		TC: O(logn)
    
*/

#include <iostream>
#include <vector>
using namespace std;


// finds the smallest number in cyclically sorted array
int findSmallestCyclicallySorted(vector<int>& arr){
	// if empty 
	if(arr.empty())
		return -1;

	// lower and upper limits
	int left = 0, right = arr.size()-1;
	// for keeping track of middle index
	int middle = -1;

	while(left < right){
		// middle index
		middle = left + (right - left) / 2;

		if(arr[middle] > arr[right]){
			left = middle + 1;
		} else {	// right element is greater than middle element
			right = middle;
		}
	}
	return left;
}

int main() {
    vector<int> arr = {23, 314, 7888, 3, 4, 5, 15, 17, 19};

    cout << findSmallestCyclicallySorted(arr);
	return 0;
}
