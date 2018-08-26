/*
    Problem:
        Given a number in base 'b1', convert the number to base 'b2'
        0 <= b1, b2 <= 16
        For numbers >= 10, use A for 10, B, ... F for 15

    Input:
        num: (string)num in b1 for conversion
        b1: base 1
        b2: base 2

    Output:
        number in base b2

    For this first we will convert the number to base 10. After that convert it to b2.
*/

#include<iostream>
#include<vector>
using namespace std;

// converts a base b1 number to base 10
/*
    To change to base 10, we multiply the number with its base values raised
    to the power of digit position
 */
int convertToDecimal(const string&  num, int base){
    int num_10 = 0;
    // check if negative
    bool negative = num[0] == '-'? true: false;

    for(int i = negative? 1:0; i < num.size(); i++){
        // multiply by base value
        num_10 *= base;
        // take out the digit from the number
        // in case the position is occupied by A, B.. F we convert it to
        // their values 10, 11,... 15
        if(isdigit(num[i])){
            num_10 += num[i] - '0';
        }
        else{   // If b1 >= 10 then it can have A, B .. occupy positions
            // since each charc from A onwards is atleast >= 10
            num_10 += num[i] - 'A' + 10;
        }
    }

    return negative ? -num_10 : num_10;
}

// converts the number from decimal to given base b2
string convertToBase(int num, int base){
    if(num == 0)
        return "";
    // now the remainder can be single or multiple digit long
    return convertToBase(num / base, base) +
           (char)(num % base < 10 ? num % base + '0': (num % base) - 10 + 'A');
}

// driver function for this task
// converts b1 --> b2
string convertBasesDriver(const string& num_b1, int b1, int b2){
    // converts the number from given base to decimal
    int num_10 = convertToDecimal(num_b1, b1);
    // convert the number from decimal to given base
    string num_b2 = convertToBase(num_10, b2);

    return num_b2;
}

int main(){
    // testing
    cout << convertToDecimal("1001", 2) << endl;
    cout << convertToBase(15, 2) << endl << endl;

    cout << convertBasesDriver("615", 7, 13);
    return 0;
}
