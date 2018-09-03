/*
    Problem:
        Run length encoding: Given a string consisiting of chars, we represent
        each same successive chars by their number followed by that char.
        Eg: aaabcddda
            3a1b1c3d1a
            aaa
            3a
        Write functions for both encoding a string and decoding a run length encoded string
    Input:
        str: string either encoded/decoded

    Output:
        encoded string or decoded string

    TC: O(n), n: no. of chars

*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<ctype.h>
using namespace std;

// for some weird reason the library function was not working
string to_string(int n){
    string term;
    while(n){
        term += n%10 + '0';
        n /= 10;
    }
    reverse(term.begin(), term.end());
    return term;
}


// does run length encoding of the string
string encodeRunLength(const string& str){
    // for storing the encoded string
    string encoded_str;
    int char_count = 1;

    // when there is only one character
    if(str.size() == 1){
        encoded_str = to_string(char_count) + str.front();
        return encoded_str;
    }

    for(int i = 1; i < str.size(); i++){

        // if the curr char is diff from the previous char,
        // then write its count
        if(str[i-1] != str[i]){
            encoded_str += to_string(char_count) + str[i-1];
            // reset the count for the next char
            char_count = 1;
        }
        else
            ++char_count;
    }

    // deal with the last char
    if(encoded_str.size() > 0)
        encoded_str += to_string(char_count) + str.back();

    return encoded_str;
}

// for decoding run length length encoded strings
string decodeRunLength(const string& str){
    // for storing the decoded string
    string decoded_str;
    // for keeping the char count
    int char_count = 0;

    for(int i = 0; i < str.size(); ){

        // check if the current char is a digit or not,
        // if it is then find the total number
        while(isdigit(str[i])){
            char_count *= 10;
            char_count += str[i] - '0';
            ++i;
        }

        // write the characters
        while(char_count > 0){
            --char_count;
            decoded_str += str[i];
        }
        // get to the next number
        ++i;
    }

    return decoded_str;
}

int main(){
    string enc_str = encodeRunLength("aaabccd");
    cout << "String: aaabccd\nEncoded:" << enc_str << "\nDecoded:"
         << decodeRunLength(enc_str)<<endl;

     enc_str = encodeRunLength("");
     cout << "String: \nEncoded:" << enc_str << "\nDecoded:"
         << decodeRunLength(enc_str)<<endl;
    return 0;
}
