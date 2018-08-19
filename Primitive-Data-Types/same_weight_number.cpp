/*
    Problem:
        Weight of a number is the number of set bits in that number.
        Given a number 'x', find a number 'y' which has the same weight as 'x' 
        but the absolute difference |x-y|is minimum and y != x

    Input:
        x = Real number

    Output:
        y = Real number 
*/

#include<iostream>
#include<vector>
#include<bits/functexcept.h>
using namespace std;

// Finds the same weight number satisfying the constraints
/* In order to have the number with same weight which is closest, we can say that
    the we need to minimize 2^m - 2^n, where m>n and m and n are the indices that
    gets swapped. And that difference is the difference between the original and 
    new number. To minimize that we take m,n as right as possible and ensuring
    that the two are not same also. Also nth position should be adjacent to minimize.  
*/
int sameWeightNumber(int x){
    // no. of bits
    int word_size = 32;
    
    for(int i = 0; i < word_size - 1; i++){
        // if the adjacent bits are not same
        if((x >> i)&1 != (x >> i+1)&1){
            // flip the bits
            x ^= (1 << i) | (1 << i+1);
            return x;
        }
    }
    // when all the bits of the number are same i.e, either 1 or 0
    throw __throw_invalid_argument;
}

int main(){
    cout << sameWeightNumber(~0);
    return 0;
}