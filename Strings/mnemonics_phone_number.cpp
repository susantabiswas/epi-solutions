/*
    Problem:
        Find all possible mnemonics for a given input number.
        Each digit key on keypad has 3-4 chars on them, except for 1 and 0.
        Find all such cmb for a number.
        Eg. 223: abd, aad ... etc

    Input:
        num: string

    Output:
        array of string
    TC: T(n) = 4T(n-1)
            = O(4^n)
*/

#include<iostream>
#include<vector>
using namespace std;

// for printing the vector elements
void printMnemonics(vector<string>& mnemonics){
    vector<string> :: iterator it;
    for(it = mnemonics.begin(); it!=mnemonics.end(); it++){
        cout << *it << endl;
    }
    cout << endl;
}

// finds mnemonics for a given number
void generateMnemonics(vector<string>& mnemonics, const string& phone_num,
                                int n, vector<string>& keypadMappings, string& curr_mnemonic){
    // when all the digits have been processed
    if( n == phone_num.size()){
        mnemonics.emplace_back(curr_mnemonic);
        return;
    }

    // try all the chars for the current digit
    for(int i = 0; i < keypadMappings[phone_num[n] - '0'].size(); i++){
        // try the current char
        curr_mnemonic.push_back(keypadMappings[phone_num[n] - '0'][i]);
        // recurse further
        generateMnemonics(mnemonics, phone_num, n + 1, keypadMappings, curr_mnemonic);
        // remove the current char to allow the next in line char
        curr_mnemonic.pop_back();
    }
}

// driver function for finding the mnemonics for a phone number
vector<string> findMnemonicsDriver(const string& phone_num){
    // for storing the different mnemonics
    vector<string> mnemonics;
    string curr_mnemonics;
    // keypad chars for each of the 9 digits
    vector<string> keypadMappings = {"0", "1", "abc", "def",
                                    "ghi", "jkl", "mno",
                                    "pqrs", "tuv", "wxyz",
                                    };


    generateMnemonics(mnemonics, phone_num, 0, keypadMappings, curr_mnemonics);
    return mnemonics;
}

int main(){
    vector<string> mnemonics= findMnemonicsDriver("123");
    printMnemonics(mnemonics);
    return 0;
}
