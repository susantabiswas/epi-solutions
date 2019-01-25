/*
	Given a real number, find its real square root. Answer will be the largest number whose
	square is atleast equal or lesser than given number
	
	Input: double
	Output: double 
	
	Solution:
		There are two imp points to note:
		1. if 0 <= num < 1 : then its square will be > num. So we set the limits 
		   as : l = num and r = 1.0
		2. if num >= 1: then we can set limits as :
			l = 0 and r = x / 2
			
		With these limits we can just use binary search for finding the sq root.
		TC: O(logn)
*/

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

typedef enum {FRACTIONAL_ONLY, NON_FRACTIONAL_ONLY} Category;
typedef enum {SMALLER, EQUAL, LARGER} State;

// decides the category to which the real number belongs to
Category decideCategoryOfRealNum(double& num){
	if (num < 1.0 )
		return FRACTIONAL_ONLY;
	else	
		return NON_FRACTIONAL_ONLY;
}

// compares two double real numbers
State compareNumbers(double& a, double& b){
	double diff = (a - b) / b;	// normalization
	
	if(diff < - numeric_limits<double>::epsilon()) // when a < b
		return SMALLER;
	else if(diff > numeric_limits<double>::epsilon())	// a > b
		return LARGER;
	else
		return EQUAL;	// a = b
}

// finds square root of real number
double findRealSquareRoot(double& num){
	// first find the category of the number
	Category category = decideCategoryOfRealNum(num);
	
	double left = -1, right = -1;
	double middle = -1;
	double sq = 0;
	
	// set the limits based on the category
	if(category == FRACTIONAL_ONLY){
		left = num;
		right = 1.0;
	} else {
		left = 1.0;
		right = num ;
	}
	
	// now search for the root using binary search
	while(compareNumbers(left, right) == SMALLER){
		// find the middle value
		middle = left + (right - left) / 2;
		sq = middle * middle;		
		
		// now check 
		if(compareNumbers(sq, num) == SMALLER){	// when the square of current number is smaller, change lower bound
			left = middle;
		}
		else if(compareNumbers(sq, num) == EQUAL){ // when the square root is found
			return middle;
		}
		else if(compareNumbers(sq, num) == LARGER){ // when the square of current number is larger, change upper bound
			right = middle;
		}
	}
	return left;
}

int main() {
	double num = 2;
	cout << findRealSquareRoot(num);
	return 0;
}
