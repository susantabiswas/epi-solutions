/*
    Problem: Count the number of set bits in binary representation of a number

    Input: Real number

    Output: No. of set bits
*/

#include<iostream>
#include<vector>
using namespace std;

// for counting no. of set bits 
short countSetBits(unsigned int x){
    short set_bits = 0;
    // traverse through the bits 
    while(x){
        set_bits += (x & 1);
        x >>= 1;
    }
    return set_bits;
}

int main(){
    cout << countSetBits(0) << endl;
    cout << countSetBits(1) << endl;
    cout << countSetBits(7) << endl;
    return 0;
}