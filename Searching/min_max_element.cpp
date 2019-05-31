/*
	Given an unsorted array of numbers, find the min and max element in min no. of comparisons.
	Input: 1D array of unsorted int
	Output: min and max numbers
	
	Solution:
		Doing linear traversal for finding takes 2n-2 comparisons. To use even lesser comparisons
		we can take do the first level of tournament selection with the array. This will take 
		n/2 comparisons for finding the winners and loser. Then finding the min and max amongst them
		takes n/2 - 1 each time. 
		Total: n/2 + 2*(n/2 - 1) = 3n/2 - 2

		TC: O(n)
    
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// finds the min and max element from array
// We return a pair where the first element is Min and second element is Max
pair<int, int> findMinMax(vector<int>& arr){
	// when there is only one element
	if(arr.size() == 1)
		return make_pair(arr[0], arr[0]);

	// for keeping track of current element pair
	pair<int, int> curr;

	// max pair with first and second numbers
	pair<int, int> min_max;
	if(arr[0] < arr[1]){
		curr = make_pair(arr[0], arr[1]);
	} else {
		curr = make_pair(arr[1], arr[0]);
	}
	// initial value for min and max
	min_max = curr;
	for(int i = 2; i < arr.size()-1; i += 2){
		// check which amongst the pair is larger
		if(arr[i] < arr[i+1]){
			curr = make_pair(arr[i], arr[i+1]);
		} else {
			curr = make_pair(arr[i+1], arr[i]);
		}
		
		// set min element
		min_max.first = curr.first < min_max.first ? curr.first : min_max.first;	
		// set max element
		min_max.second = curr.second > min_max.second ? curr.second : min_max.second;	
	}	

	// if there are odd no. of elements, one will be left
	if(arr.size() % 2 != 0){
		min_max.first = arr[arr.size() - 1] < min_max.first ? arr[arr.size() - 1] : min_max.first;	
		// set max element
		min_max.second = arr[arr.size() - 1] > min_max.second ? arr[arr.size() - 1] : min_max.second;	
	}

	return min_max;
}

int main() {
    vector<int> arr = {2, 23, -23, -442, 99, 0 , 34, 998, 634, -872};
	pair<int, int> min_max = findMinMax(arr);

	cout << "Min: " << min_max.first << " Max: " << min_max.second;
	return 0;
}
