/*
    Problem:
        Given a spreadsheet column id, convert that to its integer equivalent.
        A = 1, B = 2,..... Z = 26, AA = 27, AB = 28 ....

    Input:
        col_id: string

    Output:
        Int

    TC: O(n), n=no. of chars
*/

#include<iostream>
#include<vector>
using namespace std;

// converts a spreadsheet column to its integer equivalent
// We can treat it as base conversion problem, where the base is 26 and we just find the decimal equivalent
// of the column id with base 26
int toSpreadsheetIntEquivalent(string col_id){
    int int_equiv = 0;
    // iterate through the characters
    for(char c: col_id){
        int_equiv *= 26;
        int_equiv += c - 'A' + 1;
    }

    return int_equiv;
}

int main(){
    cout << toSpreadsheetIntEquivalent("Z") << endl << toSpreadsheetIntEquivalent("AC") << endl;
    return 0;
}
