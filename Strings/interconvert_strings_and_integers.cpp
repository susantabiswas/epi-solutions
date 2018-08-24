/*
    Problem:
        Write functions that can convert a string encoded integer to an integer and vice versa

    Input:
        str: string encoded integer
        num: int
    Output:
        num: integer equivalent
        str: string equivalent
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// converts a string to integer
// TC: O(n)
int stringToInt(string str){
    // check if the number is negative or not
    bool negative = str.front() == '-' ? true: false;
    // this stores the integer equivalent
    int num = 0;

    for(int i = negative? 1:0; i < str.size(); i++){
        // multiply the digit with the base value for its digit position
        num *= 10;
        // take out the last digit
        num  += (str[i] - '0') % 10;
    }

    return negative ? -num : num;
}

// converts an integer to its string representation
// TC: O(n)
string intToString(int num){
    // check if the number is negative
    bool negative = num < 0? true: false;
    // make the no. +ve for calculations
    if(negative)
        num = num * -1;
    // for storing the string encoded int
    string str = "";

    do{
        // take out the last digit
        str.push_back('0' + num % 10);
        num /= 10;
    }while(num);

    // add the negative sign if req
    if(negative){
        str += '-';
    }

    // reverse the string to make the number representation correct
    reverse(str.begin(), str.end());

    return str;
}

int main(){
    cout << stringToInt("") << endl << stringToInt("0") << endl << stringToInt("-21") << endl
        << stringToInt("2112") << endl;
    cout << endl << intToString(0) << endl << intToString(111) << endl << intToString(-1212) << endl;
    return 0;
}
