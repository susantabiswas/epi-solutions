/*
    Problem:
        Given a string, check if it is palindromic or not

    Input:
        s = string

    Output:
        bool

    TC: O(n), n= no. of chars
*/

#include<iostream>
#include<vector>
using namespace std;

//checks if a string is a palindrome or not
bool isPalindrome(string s){

    for(int i = 0, j = s.size() -1; i < j; i++, j--){
        if(s[i] != s[j])
            return false;
    }
    // also includes the case when the string is empty
    return true;
}

int main(){
    cout << isPalindrome("aabscaa") << endl << isPalindrome(" ") << endl <<
        isPalindrome("a") << endl << isPalindrome("aabaa") << endl << isPalindrome("aa") << endl
        << isPalindrome("") << endl;
    return 0;
}
