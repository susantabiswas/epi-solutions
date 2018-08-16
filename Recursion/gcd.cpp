/*
    Problem:
        Find the GCD( Greatest Common Diviser) of two numbers a and b.
        TC: O(max(a, b)) or O(n), where n=no. of bits 
        Since every time the function is called one of the numbers is atleast halved,
        that means the function s called till a number doesn't becomes zero, so 
        at max it can last for max(a, b) of bits
    Input:
        Real numbers a and b

    Output:
        GCD of 'a' and 'b'
*/

#include<iostream>
#include<vector>
using namespace std;

// finds the GCD of two numbers
int gcd(const int a, const int b){
    // if the bigger number is zero, that means the 'b' 
    // can divide 'a'
    if(a == 0)
        return b;
    // We check which is the bigger number frst, then
    // the recurse with the remainder and diviser
    if(a > b)
        return gcd(a % b, b);
    else
        return gcd(b % a, a);
}


int main(){
    cout << gcd(20, 1) << endl;
    return 0;
}