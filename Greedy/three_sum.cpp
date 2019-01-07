/*	
	Given an array of numbers and a sum, find whether we can get that number by adding three numbers 
	from the array. A number can be repeated.
	
	Input: array of num, sum
	Output: array of those three numbers if it exists, else return empty array
	
	Solution:
		
	TC: O(n^2) + O(nlogn) ~ O(n^2)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Finds if there are two numbers whose sum equals given number 
// It is assumed that the array of numbers is sorted
// TC: O(n)
vector<int> hasTwoSum(vector<int>& arr, int sum){
	vector<int> nums;
	
	int i = 0, j = arr.size() - 1;
	
	while(i <= j){
		// when the sum is found
		if(arr[i] + arr[j] == sum){
			nums.emplace_back(arr[i], arr[j]);
			break;
		}
		
		// if sum is lesser
		if(arr[i] + arr[j] > sum){
			--j;
		}
		// if sum is greater
		else if(arr[i] + arr[j] < sum){
			++i;
		}
	}
	
	return nums;
}

// finds if there are three numbers whose sum equals given number 
// It is assumed that the array of numbers is sorted
vector<int> hasThreeSum(vector<int>& arr, int& sum){
	// sort the numbers
	sort(arr.begin(), arr.end());
	vector<int> nums;
	
	/*// for each number we will see if sum - num[i] is possible using two numbers
	for(int i = 0; i<arr.size(); i++){
		auto nums = hasTwoSum(arr, sum - arr[i]);
		
		if(!nums.empty()){
			nums.emplace_back(arr[i]);
			break;
		}
	}*/
	return nums;
}

int main() {
	vector<int> arr = {12, 11, 2, 3, 7, 1, 10};
	int sum = 8;

	vector<int> nums = hasThreeSum(arr, sum);
/*	for(auto el: nums)
		cout << el << " ";*/

	return 0;
}
