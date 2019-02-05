/* 
	Given two sorted arrays. First array has extra space at the back, big enough to accomodate 
	the other array. Merge the two arrays in such a way that the resultant array is also sorted.
	Merged array should reside in the first array itself.

	Input: two int sorted arrays
	Output: array 1 which has merged values 

	Solution:
		Since extra space is at the back we can just take indices for each array pointing to the 
		last element and then start traversal backwards.
		The larger of the two arrays will put its value at the current index at the back and decrement
		its index.

		TC: O(n + m)
		SC: O(1)
*/

#include <iostream>
#include <vector>
using namespace std;

// merges two already sorted array into one
vector<int> mergeSortedArrays(vector<int>& a, vector<int>& b,
					const int& M, const int& N) {
	int i = M - 1;	// index of last non vacant pos. in array 1 
	int j = N - 1;	// last index of array 2
	int write_idx = a.size() - 1;	// last writable index of array 1
	
	while(i >= 0 && j >= 0) {
		// write the correct value and decrement the index for that array too
		a[write_idx--] = a[i] > b[j] ? a[i--] : b[j--];
	}
	
	// fill the rest of elements of whichever array is left
	while(i >= 0)
		a[write_idx--] = a[i--];
	while(j >= 0)
		a[write_idx--] = b[j--];
		
	return a;
}

ostream& operator<<(ostream& out, vector<int> arr) {
	for(const auto& a: arr)
		cout << a << " ";
	cout << endl;
}

int main() {
	vector<int> a = {-22, 2, 5, 6};
	a.resize(10);
	vector<int> b = {-33, 0, 4, 5, 7, 8};

	cout << mergeSortedArrays(a, b, 4, 6);
	return 0;
}
