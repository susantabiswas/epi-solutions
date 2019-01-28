/*
	Given an unsorted array of distinct elements, find the Kth largest element.
	K is 1 indexed.
	Input: int array
	Output: int
	
	Solution:
		We can randomly select a pivot element, then find its pivot position,
		Now:
			if the pivot index is K-1: then done
			else if pivot index > k-1:
				means upper limit = pivot_index-1
			else if pivot index < k-1:
				lower_limit = pivot_index + 1

		TC: O(n) avg case   [T(n) = T(n) + T(n/2)]
			O(n^2) worst case
    
*/

#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>
using namespace std;

// for swapping elements
void swapElements(vector<int>& arr, int left, int right){
	int temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}

// Places the pivot element to its correct position
template < typename Compare >
int placePivotElement(vector<int>& arr, int pivot_index, int left, int right, Compare compare){
	int pivot_value = arr[pivot_index];
	// for keeping track of last index of larger elements till now
	int curr_big = left;

	// swap the pivot with last element 
	swapElements(arr, pivot_index, right);
	
	// we use two pointers for arranging the elements 
	// for our case for finding the kth largest element, we will first
	// have all elements greater than the pivot then all elements smaller than pivot
	for (int i = left; i < right; i++) {
	
		// we do swapping only when the current element is greater than pivot
		if (compare(arr[i], pivot_value)) {	
			swapElements(arr, i, curr_big);
			++curr_big;
		}
	}
	// swap the pivot to its correct position
	swapElements(arr, curr_big, right);
	
	return curr_big;
}

// finds the kth largest element
template < typename Compare >
int findKthLargestElement(vector<int>& arr, int k, Compare compare){
	// when the array size is lesser than k
	if(arr.size() < k)
		return numeric_limits<int>::min();
	
	int left = 0, right = arr.size()-1;
	int pivot_index = 0;
	
	// generate a random index for pivot
	default_random_engine random_gen((random_device())());
	
	while(left <= right){
		// generate random index
		pivot_index = uniform_int_distribution<int>{left, right}(random_gen); 		

		// find the pivot partition position
		int partition_pos = placePivotElement(arr, pivot_index, left, right, compare);
		
		if (partition_pos == k - 1){
			return arr[partition_pos];
		}
		else if (partition_pos > k - 1){
			right = partition_pos - 1;
		}
		else if (partition_pos < k - 1){
			left = partition_pos + 1;
		}
	}
}


int main() {
	int k = 4;
    vector<int> arr = {2, 23, -23, -442, 99, 10 , 34, 998, 634, -872};

	cout << k << "th largest: " << findKthLargestElement(arr, k, greater<int>());
	cout << endl;
	

	sort(arr.begin(), arr.end(), greater<int>());
	// verify the result using sorted array
	for(auto a: arr){
		cout << a << " " ;
	}
	cout << "\nUsing sorting: "<<arr[k-1];
	return 0;
}
