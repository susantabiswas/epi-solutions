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
double findPower1(float x, int n){
    // when power is 0
    if(n == 0)
        return 1;
    // if negative power 
    if(n < 0 && n == -1)
        return 1.0/x;

    double result = findPower1(x, n / 2);

    // if power is even    
    if(n % 2 == 0){
        return result * result;
    }
    else{
        // if it is odd, we can subdivide the power as even number multiplied by that no.
        return result * result * x;
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
        // if the current LSB of power is 1 or we can say if the power is odd
        // when the power is odd we multiply the number thrice
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
    cout << findPower1(2, 3) << ", " << findPower2Iter(2,3)<< endl;
    cout << findPower1(2, 4) << ", " << findPower2Iter(2, 4) << endl;
    cout << findPower1(2, -1) << ", " << findPower2Iter(2, -1) << endl;
    cout << findPower1(2, -2) << ", " << findPower2Iter(2, -2) << endl;
    cout << findPower1(3, 2) << ", " << findPower2Iter(3, 2) << endl;
    cout << findPower1(3, 3) << ", " << findPower2Iter(3, 3) << endl;
    cout << findPower1(3, -1) << ", " << findPower2Iter(3, -1) << endl; 

    return 0;
}