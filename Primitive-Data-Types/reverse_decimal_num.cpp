/*
	Reverse a number without using extra space
	
	input: int 
	Output: reversed number (int)
	
	TC: O(n), n: no. of digits in number
*/
#include<iostream>
#include<cmath>
using namespace std;

// reverses the input number without extra space
int reverseNumber(int num){
	int reversed_num = 0;
	
	while(num){
		reversed_num *= 10;
		// add the last digit
		reversed_num += num % 10;
		// remove the last digit from the original num
		num /= 10;
	}
	
	return reversed_num;
}


int main(){
	int num = 123;
	cout << reverseNumber(num);
	return 0;
}
