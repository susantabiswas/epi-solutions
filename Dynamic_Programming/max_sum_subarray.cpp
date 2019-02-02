/*	
	Given an array of integers. Find the maximum sum subarray.

	Input: int array
	Output: int

	Solution:
		For any index 'i', the max sum till there is the total sum till there
        minus the min sum subarray.
        We keep track of the total sum and min_subarray sum.
        At every index we check if total sum - min subarray is giving
        us the max value or not. 
		TC: O(n)
*/

#include <iostream>
#include <unordered_map>
using namespace std;

// finds the max subarray sum value
long findMaxArraySum(const vector<int>& arr) {
    long max_sum = 0;   // tracks max sum
    long sum = 0;   // tracks total sum
    long min_sum = 0;   // tracks sum of min value subarray
    
    
    for (const auto& el : arr) {
        // we compute the total sum till current index
        sum += el;

        // track the min sum value subarray til current index
        if (sum < min_sum)
            min_sum = sum;
        // check if removing some min value earlier subarrray
        // gives us a max value subarray
        if (sum - min_sum > max_sum)
            max_sum = sum - min_sum;
    }
    return max_sum;
}

int main() {

    vector<int> arr = {-7, 2, 3, -6, 5, 6};
    cout << findMaxArraySum(arr);
    return 0;
}
