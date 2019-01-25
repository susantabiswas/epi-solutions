#include <iostream>
#include <vector>
using namespace std;

// finds the integer square root
int findIntegerSquareRoot(int n){
	// lower and upper limits
	int left = 0, right = n;
	// for keeping track of middle number
	int middle = 0;
	int sq_val = 0;
	
	while(left <= right){
		// middle number
		middle = left + (right - left) / 2;
		// square of current middle number
		int sq_val = middle * middle;
		
		// check its square value
		// return if its value is equal 
		if(sq_val == n)
			return middle;
			
		// if the middle is lesser than the target number, then increase the 
		// lower number by 1
		else if(sq_val < n){
			left = middle + 1;			
		}
		else if(sq_val > n){	// if the middle num is greater than all after that are greater
			right = middle - 1;
		}
	}
	return left - 1; // as left-1 is always lesser than the number, and if current left is 
					// greater than left-1 is the closest answer
}

int main() {
	int num = 1;
	cout << findIntegerSquareRoot(num);
	return 0;
}
