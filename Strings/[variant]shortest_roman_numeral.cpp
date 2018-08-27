/*
    Problem:
        For a given integer, write the smallest roman numeral for it
        I:1, V:5, X:10, L:50, C:100, D:500, M:1000

    Input:
        roman_num: string

    Output:
        shortest roman num: string

    TC: O(n), n: int num
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


// Int to roman symbols mappings
unordered_map<int, string> romanMappings = {{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"},
                                            {40, "XL"}, {50, "L"}, {90, "XC"},
                                            {100, "C"}, {400, "CD"}, {500, "D"},
                                            {900, "CM"}, {1000, "M"}};
// roman number values
/* Possible Roman symbols:
    I:1, V:5, X:10, L:50, C:100, D:500, M:1000
    1. I before V and X: IV:4 and IX:9
    2. X before L and C: XL:40 and XC:90
    3. C before D and M: CD:400 and CM:900
 */
vector<int> romanVals = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
// converts roman number to integer
/*
    We divide the number by the largest roman value that is smaller than
    the roman number.
*/
string shortestRomanfromInt(int num){
    string roman_num;

    if(num == 0)
        return "";

    // start with the largest value
    for(int i = romanVals.size() - 1; i >= 0 ; i--){
        if(romanVals[i] <= num){
            // print the sym the no. of times it can divide
            for(int j = 0; j < num / romanVals[i]; j++)
                roman_num += romanMappings[romanVals[i]];

            return roman_num + shortestRomanfromInt(num % romanVals[i]);
        }
    }
}

int main(){
   cout << shortestRomanfromInt(10) << endl << shortestRomanfromInt(59) << endl
      << shortestRomanfromInt(900) << endl << shortestRomanfromInt(1300) << endl;
    return 0;
}
