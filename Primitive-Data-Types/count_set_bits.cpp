/*
    Problem: Count the number of set bits in binary representation of a number

    Input: Real number

    Output: No. of set bits
*/

#include<iostream>
#include<vector>
using namespace std;

// for counting no. of set bits 
// Tc: O(n), n=no. of bits in number representation
short countSetBits(unsigned int x){
    short set_bits = 0;
    // traverse through the bits 
    while(x){
        set_bits += (x & 1);
        x >>= 1;
    }
    return set_bits;
}

// counts set bits
// TC: O(s), s=no. of set bits
// we can efficiently count the set bits by going through only the set bit
// using the x & (x-1) expression we can clear the rightmost set bit
short countSetBits2(unsigned int x){
    int set_bits = 0;
    while(x){
        set_bits++;
        // clear the rightmost bit
        x = x & (x-1);
    }

    return set_bits;
}

int main(){
    cout << countSetBits(0) << ", " << countSetBits2(0) << endl;
    cout << countSetBits(1) << ", " << countSetBits2(1) << endl;
    cout << countSetBits(7) << ", " << countSetBits2(7) << endl;
    return 0;
}