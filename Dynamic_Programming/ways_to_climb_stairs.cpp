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


/*int waysToClimbStairsTabulation(int n, int k) {
	// each row indicates that we are using all the steps till that
	// eg: row 2 means using steps of 1 and 2.
	vector<vector<int>> cache(k + 1, vector<int>(n + 1, 0));
	
	// ways to climb stairs using the max no. of 'k' stairs
	for(int i = 1; i <= k; i++) {
		// zero steps can always be acheived
		cache[i][0] = 1;
		
		for(int j = 1; j <= n; j++) {
			// 'j' steps can be reached by either including current
			// no. of steps or by not taking it
			int include_step = i <= j ? cache[i][j - i] : 0;
			int exclude_step = i >= 1 ? cache[i - 1][j] : 0;
			
			cache[i][j] = include_step + exclude_step;
		}	
	}
	
	for(auto arr: cache){
		for(auto a: arr)
			cout<<a <<" ";
		cout << endl;
	}
	return cache.back().back();
}*/

// finds the number of ways in which 'n' steps can be climbed using max of 'k' steps
int waysToClimbStairsMemoizationHelper(int n, int k, vector<int>& steps_ways) {
	// when we have reached
	if(n == 0)
		return 1;
	if(k <= 0)
		return 0;
		
	if(steps_ways[n] == 0) {
		// for each target, find the no. of steps required starting from bottom 
		for(int i = 1; i <= k && (n - i) >= 0; i++) {
			steps_ways[n] += waysToClimbStairsMemoizationHelper(n - i, k, steps_ways);
		}
	}

	return steps_ways[n];
}

int waysToClimbStairsMemoization(int n, int k) {
	// each entry stores the no. of ways in which that many steps can be climbed
	// steps_ways[i] = summation(n - i) for all 1 <= i <= k
	vector<int> steps_ways(n + 1, 0);

	int ways = waysToClimbStairsMemoizationHelper(n, k, steps_ways);
	
	for(auto arr: steps_ways)
			cout<<arr <<" ";
		cout << endl;
	
	
	return ways;
}

int main() {
	int n = 4;
	int k = 2;

	cout << waysToClimbStairsMemoization(n, k);	

//	cout << endl << waysToClimbStairsTabulation(n, k);
	return 0;
}
