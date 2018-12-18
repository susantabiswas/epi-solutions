/*
	Problem: Given a decimal number, check whether it is palindromic or not wittout 
	using extra space. 
	NOTE: By decimal, it means the the number is in base 10 and not that it is a float or double
	value. Also negative numbers are not palindromic because of sign.
	
	Input: decimal num(int)
	Output: bool
	
	TC: O(n), n: no. of digits
	
*/

#include<iostream>
#include<cmath>
using namespace std;

// Checks if the number is palindromic or not
/*
	Instead of using an array for storing the number as a series of digits, we can directly access
	the first and last digit and check if they are same or not. Then we reduce the number by 
	ignoring the previous first and last digits. If at any point the digits are different we return false
*/
bool isPalindromic1(int num){
	// check if the number is negative or not
	if(num < 0)
		return false;
		
	// find the number of digits in the number
	int num_digits = floor( log10(num) )  + 1;
	
	// highest place value, this will be used for getting the MSB
	int place_val = pow(10, num_digits - 1);
	
	// for storing the first and last digits
	int first = 0, last = 0;
	
	for(int i = 0; i < num_digits/2; i++){
		// get the first digit
		first = num / place_val;
		first %= 10;
		
		// get the last digit
		last = num % 10;
	
		// check if the digits differ or not
		if(last != first)
			return false;
		
		// remove the last digit
		num = num / 10;
		// decrease the place value. We divide it by 100 to account for the removal
		// of last digit also
		place_val = place_val / 100;
	}

	return true;
}

// checks if the number is palindromic or not without extra space
// Here instead of using place value for accessing the MSD(Most significant digit), we straight 
// away remove the digit in every iteration.
bool isPalindromic2(int num){
	// check if the number is negative
	if(num < 0)
		return false;
	
	// find the number of digits
	int num_digits = floor(log10(num))  + 1;
	
	// mask for getting the number excluding the MSD, we take the second highest
	// place value
	int place_val = pow(10, num_digits - 1);
	
	for(int i = 0; i< num_digits/2 ; i++){
		// check if the digits are same
		if(num % 10 != num/place_val){
			return false;
		}
		
		// remove the first digit
		num = num % place_val;
		// remove the last digit
		num = num / 10;
		// reduce the place value
		place_val = place_val / 100;
	}
	
	return true;
}

int main(){
	int num = 0;
	
	// check if the number is a palindrome or not
	cout << isPalindromic2(num);
	
	return 0;
}
