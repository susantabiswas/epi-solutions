/*
    Problem:
        For a given integer, write the smallest roman numeral for it
        I:1, V:5, X:10, L:50, C:100, D:500, M:1000

    Input:
        roman_num: string

    Output:
        shortest roman num: string

    TC: O(n), n: no. of symbols
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// converts roman number to integer
/*
    The integer equivalent is the sum of the values of the symbols except for the
    symbols where the smaller symbol preceedes the greater symbol, in that case the value is
    (value greater sym - value smaller sym)
    Eg: XIV: 10 + (5-1)
*/

int romanToInteger(const string& roman_num){
    // resultant int
    int result = 0;

    // roman symbols mappings
    unordered_map<char, int> romanMappings = {{'I',1}, {'V',5}, {'X',10}, {'L',50},
                                                {'C',100}, {'D',500}, {'M',1000}};
    // scan through the symbols
    for(int i = 0; i < roman_num.size(); i++){
        // see the next symbol
        if(i+1 < roman_num.size() && roman_num[i+1] > roman_num[i]){
            result += ((romanMappings[roman_num[i+1]]) - (romanMappings[roman_num[i]]));
                // increment index since the next index has already been accounted for
            ++i;

        }
        else
            result += romanMappings[roman_num[i]];
    }
    return result;
}

int main(){
    cout << romanToInteger("XIV") << endl << romanToInteger("XIVII") << endl
        << romanToInteger("VIII") << endl;
    return 0;
}
