/*
    Problem:
        Find the nth power of a number

    Input:
        Real no. x, power n

    Output:
        x raised to n
*/
#include<iostream>
#include<vector>
using namespace std;

// finds the square of the number
// TC: O(logn), n=power
// the power of can be broken down in terms of squares of smaller numbers
double findPower(int num, int i){
	// base case
	if(i == 0)
		return 1;
		
	double val = findPower(num, i/2);
	
	// if the power is even
	if( i % 2 == 0){
		return val * val;
	}
	// if the power is odd
	else{
		// if positive power
		if( i > 0)
			return val * val * num;
		// if negative power
		else if( i < 0)
			return val * val * 1.0/num;
	}
}

// finds the nth power of a number recurrsively
double findNthPowerRec(int num, int n){
	// when the number is zero
	if(num == 0)
		return 0;
	// base case when the power is zero
	if(n == 0)
		return 1;
	// when the exponent is negative
	if(n == -1)
		return 1.0/num;
	// find the value by making further calls
	double val = findNthPowerRec(num, n >> 1);
	// if the last digit is 1, that means the exponent is formed by adding exponent 1, so multiply 
	// by the number. Eg: 2^(101): 2^(10)*2^(10)*2^(1)
	if(n & 1) {
		return num * val * val;
	}
	else{
		return val* val;
	}
}

// finds the nth power of a number using the bit representation iteratively.
// TC: O(n), n=no. of bits
double findPower2Iter(double x, long long n){
    double result = 1.0;
    
    // if the power is negative 
    if(n < 0){
        x = 1.0 / x;
        // make the power positive now that x has been made 1/x
        n = -1 * n;
    }

    // till the power is not zero
    while(n){
        // if the last digit is 1, that means the exponent is formed by adding exponent 1, so multiply 
	// by the number. Eg: 2^(101): 2^(10)*2^(10)*2^(1)
        if(n & 1)
            result = result * x;
        // find the square of current number for the next iteration
        x = x * x;
        // reduce the power by a factor of 2
        n >>= 1;
    }
    return result;
}


int main(){
    cout << findPower(2, -3) << ", " << findPower2Iter(2,-3)<< endl;
    cout << findNthPowerRec(2, 4) << ", " << findPower2Iter(2, 4) << endl;
    cout << findNthPowerRec(2, -1) << ", " << findPower2Iter(2, -1) << endl;
    cout << findNthPowerRec(2, -2) << ", " << findPower2Iter(2, -2) << endl;
    cout << findNthPowerRec(3, 2) << ", " << findPower2Iter(3, 2) << endl;
    cout << findNthPowerRec(3, 3) << ", " << findPower2Iter(3, 3) << endl;
    cout << findNthPowerRec(3, -1) << ", " << findPower2Iter(3, -1) << endl; 

    return 0;
}
