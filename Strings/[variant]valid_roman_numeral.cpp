/*
    Problem:
        Given a number written in roman, check if it is valid or not
        I:1, V:5, X:10, L:50, C:100, D:500, M:1000

    Input:
        roman_num: string

    Output:
        bool

    TC: O(n), n: no. of symbols
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// checks if a roman number is valid or not
/*
    The roman number is a sequence of symbols in descending order except
    for some cases, where a smaller sym can appear immediately before a larger symbol
    The cases are:
    1. I before V and X
    2. X before L and C
    3. C before D and M
    Also these cases cannot occur immediately one after another
    Eg: DXCIV is valid but IXC is invalid
*/
bool isValidRoman(const string& roman_num){
    // keeps track of whether an exception case has occured or not recently
    bool exception_case = false;
    // length of roman number
    int n = roman_num.size();

    // roman symbols mappings
    unordered_map<char, int> romanMappings = {{'I',1}, {'V',5}, {'X',10}, {'L',50},
                                                {'C',100}, {'D',500}, {'M',1000}};

    for(int i = 0; i < n; i++){
        // when the next sym is greater than the current sym
        if(i+1 < n && romanMappings[roman_num[i]] < romanMappings[roman_num[i+1]]){
            // check if symbols follow the valid exceptions
            if(romanMappings[roman_num[i]] == 'I'){
                if(romanMappings[roman_num[i+1]] != 'X' && romanMappings[roman_num[i+1]] != 'V')
                    return false;
            }
            else if(romanMappings[roman_num[i]] == 'X'){
                if(romanMappings[roman_num[i+1]] != 'C' && romanMappings[roman_num[i+1]] != 'D')
                    return false;
            }
            else if(romanMappings[roman_num[i]] == 'C'){
                if(romanMappings[roman_num[i+1]] != 'D' && romanMappings[roman_num[i+1]] != 'M')
                    return false;
            }

            // if none one of the above cases were true, that means
            // this was a valid exception
            if(!exception_case)
                exception_case = true;
            else    // when there is an exception case before this
                return false;
        }
        // when the current case is not of exception case, then
        // make the recent exception_case as false;
        else
            exception_case = false;
    }

    return true;
}


int main(){
    cout << isValidRoman("XIV") << endl << isValidRoman("IXC") << endl
        << isValidRoman("DXCIV") << endl;
    return 0;
}
