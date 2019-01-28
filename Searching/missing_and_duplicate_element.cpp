/*
	Given an array of 'n' int whose values lie in [0, n-1]. There is one number which has been repeated twice.
	Find the duplicate number and the number of the range[0, n-1] missing from the array.

	Input: int array
	Output: int
	
	Solution:
		Take the XOR of [0, n-1] and of the array. Since XOR of same value is 0. Now since
		the array has all the values from [0, n-1] except for one, so on doing XOR every number will cancel,
		only the duplicate and missing numbers will be left.
		i.e final XOR result = missing XOR duplicate
		Since they are different, so in XOR there must be some set bits.
		We take any of the set bits and take XOR for all numbers in array as well in [0, n-1] with
		set bit at that position.

		XOR of these will give either duplicate or missing, since we didn't knew in first place which one
		of the two had set bit at that position.

		To know which it is, we search for it in array, if found then it is duplicate 
		else it is the missing number 

		TC: O(n)
    
*/

#include <iostream>
#include <vector>
using namespace std;

struct MissingAndDuplicate{
	int missing;
	int duplicate;
};

// finds the missing and duplicate numbers from the array
MissingAndDuplicate findMissingAndDuplicateNumber(vector<int>& arr){
	// first take XOR of both the range and array
	int arr_xor = 0, range_xor = 0;
	int miss_xor_dup = 0;
	// this will store either duplicate or missing number
	int unknown_num = 0;

	// stores XOR of number with kth set bit
	int xor_kth_bit_arr = 0, xor_kth_bit_range = 0;

	for(int i = 0; i < arr.size(); i++){
		arr_xor ^= arr[i];
		range_xor ^= i;
	}

	// now get missing XOR duplicate value
	miss_xor_dup = arr_xor ^ range_xor;
	
	// now go for the first set bit and create a mask of it
	int set_kth_bit_mask = miss_xor_dup & ~(miss_xor_dup - 1);

	// take XOR of all those with set bit as that of set_bit_mask
	for (int i = 0; i < arr.size(); i++) {
		// if the current number in array has a set bit at kth position
		if(arr[i] & set_kth_bit_mask){
			xor_kth_bit_arr ^= arr[i];
		}

		// if the current number in range has a set bit at kth pos.
		if(i & set_kth_bit_mask){
			xor_kth_bit_range ^= i;
		} 
	}

	// this can be either duplicate or missing number
	unknown_num = xor_kth_bit_range ^ xor_kth_bit_arr;

	// if this number is found in the array then it is duplicate number otherwise it is the 
	// missing number
	bool found = false;
	for(int a: arr){
		if(a == unknown_num){
			found = true;
			break;
		}
	}

	if(!found) {
		return {unknown_num, miss_xor_dup ^ unknown_num};
	} else {
		return {miss_xor_dup ^ unknown_num, unknown_num};
	}
}

int main() {
	// given range : 0-10, with 4 missing
	vector<int> arr = {0, 1, 2, 3, 5, 5, 6, 7, 8, 9, 10};

	MissingAndDuplicate miss_dup = findMissingAndDuplicateNumber(arr);
	cout << "Missing: " << miss_dup.missing << endl << "Duplicate: "<< miss_dup.duplicate<<endl;

	return 0;
}
