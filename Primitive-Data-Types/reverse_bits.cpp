/*
    Problem:
        Reverse the bits of a number

    Input:
        x = number for reversal     

    Output:
        reversed number 
    TC: O(n), n = no. of bits
*/

#include<iostream>
#include<vector>
using namespace std;

// Reverses the bits
int reverseBits(int x){
    // for storing the reversed bits representation
    int reversed_bits = 0;

    while(x){
        // left shift the number
        reversed_bits <<= 1;
        // retrieve the LSB of original and make it the LSB of reversed number 
        reversed_bits |= x & 1;
        // right shift the original number
        x = x >> 1;
    }
    return reversed_bits;
} 

int main(){
    cout << reverseBits(11);
    return 0;
}