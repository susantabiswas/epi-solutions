/* 
	Given the 'n', the number of steps to climb and 'k', the number of steps you can take for climbing.
	Find the number of ways in which 'n' steps can be climbed.

	Input: int, int
	Output: int
	
	Solution:
		The idea is simple, for the current 'n' we can use all steps lesser than 'n'. So for 
		each step i <= k, we can either take it or leave it. If we take it then
		next we need to cover (n-i) steps. Again we decide which step to take out of all steps.

		Base case is when n == 0, it means we have reached.
		TC: O(nk), O(k) is taken for each 'n'
		SC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

// using memoization
// TC: O(nk)
// SC: O(nk), since we are using a 2d array
int waysToClimbStairsHelperMemoization(int n, int k, vector<vector<int>>& cache) {
	if(n == 0)
		return 1;

	// if cache value is available 
	if(cache[n][k] != 0)
		return cache[n][k];
	
	// if current step is larger
	if(k > n)
		return cache[n][k] = waysToClimbStairsHelperMemoization(n, k - 1, cache);

	for(int i = 1; i <= k; i++)
		cache[n][k] += waysToClimbStairsHelperMemoization(n - i, i, cache);
	return cache[n][k];
}

int waysToClimbStairsMemoization(int n, int k) {
	// each row indicates that we are using all the steps till that
	// eg: row 2 means using steps of 1 and 2.
	vector<vector<int>> cache(k+1, vector<int>(n + 1, 0));
	return waysToClimbStairsHelperMemoization(n, k, cache);
}

// finds the number of ways in which 'k' steps can be climbed
int waysToClimbStairsTabulationHelper(int n, int k, vector<int>& steps_ways) {
	// when we have reached
	if(n == 0)
		return 1;
	
	// if the value is already cached then return
	if(steps_ways[n] != 0)
		return steps_ways[n][k] = steps_ways[n];
	
	// if current step value is greater than the no. of steps left to climb
	if(k > n)
		return waysToClimbStairsTabulationHelper(n, k-1, steps_ways);

	for(int i = 1; i <= k; i++) {
		steps_ways[n] += waysToClimbStairsTabulationHelper(n - i, i, steps_ways);
	}

	return steps_ways[n];
}

int waysToClimbStairsTabulation(int n, int k) {
	// each entry stores the no. of ways in which that many steps can be climbed
	// steps_ways[i] = summation(n - i) for all 1 <= i <= k
	vector<int> steps_ways(n + 1, 0);

	return waysToClimbStairsTabulationHelper(n, k, steps_ways);
}

int main() {
	int n = ;
	int k = ;

	cout << waysToClimbStairsTabulation(n, k);	
	return 0;
}
