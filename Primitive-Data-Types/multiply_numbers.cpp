/*
    Problem:
        Multiply two non negative numbers only using bitwise operators

    Input:
        x = 1st number
        y = 2nd number      

    Output:
        product of x and y
*/

#include<iostream>
#include<bitset>
using namespace std;

// adds two numbers using bit operators
unsigned Add(unsigned sum, unsigned y) {
    unsigned new_sum = 0, carry_in = 0, carry_out = 0, k = 1;
    unsigned temp_sum = sum, temp_y = y;
    
    while(temp_sum || temp_y) {
        // get the bits at kth position
        unsigned sum_k = sum & k, y_k = y & k;
        // check if a carry bit will be formed or not
        carry_out = (sum_k & y_k) | (sum_k & carry_in) | (y_k & carry_in);
        // set the bit at kth position
        new_sum = new_sum | (carry_in ^ sum_k ^ y_k);
        // update carry
        carry_in = carry_out << 1;
        k <<= 1, temp_sum >>= 1, temp_y >>= 1; 
    }
    return new_sum | carry_in;
}

// multiplies two numbers using bit operators only
unsigned Multiply(unsigned x, unsigned y) {
    unsigned sum = 0;
    // since this is for binary numbers, we have only 1
    // or 0. For multiplication with 1, we get the same 
    // number otherwise 0
    // Here y is multiplied by x
    while(x) {
        if(x & 1)
            sum = Add(sum, y);
        // since y is added to the total and each time it is
        // shifted by 1 step in every level
        y = y << 1;
        x = x >> 1;
    }
    return sum;
}

int main(){
    unsigned x = 13, y = 9;
    unsigned prod = Multiply(x, y);
    cout << prod;
    return 0;
}