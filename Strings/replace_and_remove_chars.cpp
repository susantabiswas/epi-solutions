/*
    Problem:
        Given an array of characters. There are two operations to be performed on these characters:
        'a': replace it with 'dd'
        'b': remove the character from the string
        Also given is the size of the array currently having the characters. The array is large
        enough to accomodate the characters after applying the operations

    Input:
        str: array of chars
        n: no. of characters

    Output:
       Array of chars with applied ops

    TC: O(n)
*/

#include<iostream>
#include<vector>
using namespace std;

// for doing the specified operations
char* replaceAndRemove(char str[], int n){
    // First we remove 'b's from the string
    // then we start the traversal from the back and scan the characters
    // if a character is 'a', then we write 'd' two times
    // else we write any other character once

    // remove all the 'b's
    int write_idx = 0;
    // for keeping count of 'a's
    int a_count = 0;

    for(int i = 0; i < n; i++){
        // when 'b' is not encountered, write the character
        if(str[i] != 'b')
            str[write_idx++] = str[i];
        if(str[i] == 'a')
            ++a_count;
    }

    // now we traverse from the back and do operations for 'a'
    // resultant array size
    int new_size = write_idx + a_count;
    // add the string termination character at the end
    str[new_size] = '\0';
    for(int i = new_size - 1, j = write_idx - 1; j>=0; j--,i--){
        // when 'a' is encountered
        if(str[j] == 'a'){
            // write 'd' two times
            str[i--] = 'd';
            str[i] = 'd';
        }
        else{
            str[i] = str[j];
        }
    }

    return str;
}

int main(){
    char str[] = "aaa";

    cout << replaceAndRemove(str, 3) << endl;
    return 0;
}
