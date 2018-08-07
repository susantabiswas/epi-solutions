/*
    Problem:Check the parity of the bit pattern. 
            Parity is 1 if the no. of set bits is odd, otherwise it is 0.  

    Input:Real number          
    Output:bool        
*/

#include<iostream>
#include<vector>
using namespace std;

// sets parity by looking at the odd bits. We take XOR of set bits
// XOR of odd no. of 1s is 1 and 0 for even no. of 1s.
// TC:O(n), n=no. of bits 
bool parity1(unsigned int x){
    bool parity = 0;

    while(x){
        parity = parity ^ (x & 1);
        x >>= 1;
    }
    return parity;
}

// Since XOR is associative as well as commutative, we canuse that fact to 
// divide the bit pattern into segments and subsegments. We find the XOR for the
// smallest segment and work our way up
// Tc: O(logn), n=no. of bits
bool parity2(unsigned int x){
    short parity = 0;
    return parity;
}

// We traverse only the set bits
// Tc: O(k), k=no. of set bits
bool parity3(unsigned int x){
    short parity = 0;
    return parity;
} 

int main(){
    
    for(size_t i = 0; i < 10; i++){
        cout << i << ": " << parity1(i) << endl;
    }
    
    return 0;
}

