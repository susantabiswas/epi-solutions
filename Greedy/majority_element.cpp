/* 
	Given an array of elements, where a number exists atleast floor(n/2). Find this 
	majority element.
	
	Input: array of numbers
	Output: int
	
	Solution:
		The count of majority element will be greater than n/2. That means if we start counting for
		it and for every element that is not majority element, we decrement the count, we will 
		still end up with atleast 1 count of majority element.
		
		So we start with the first element and assume it to be majority element, if the next 
		element is same then ++count, else --count. If count becomes zero then we make
		the element at that position as majority and continue.
		
	Tc: O(n)
*/

#include <iostream>
#include<vector>
using namespace std;

// finds majority element
int findMajorityElement(vector<int>& arr){
	// count value for element
	int c = 0;
	int majority = arr[0];
	
	for(int num: arr){
		if(num == majority)
			++c;
		else
			--c;
			
		// if count is zero, then change the majority element
		if(c <= 0){
			c = 1;
			majority = num;
		}
	}
	
	return majority;
}

int main() {
	vector<int> arr = {1, 1, 233, 1, 9, 1, 9, 1};
	
	cout << findMajorityElement(arr);
	return 0;
}
