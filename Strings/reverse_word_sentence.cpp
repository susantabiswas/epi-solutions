/*
    Problem:
        Given a string sentence, reverse all the words in the sentence
        E.g: Coding and gaming ---> gaming and Coding

    Input:
        sentence: string

    Output:
        resultant string
    TC: O(n), n: no. of chars.
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Reverses the words in the string sentence
/*
    First reverse the individual words and then reverse the entire string
 */
string reverseWordsSentence(string sentence){
    // reverse the individual words
    // starting index
    int start = 0, end_pos;
    while((end_pos = sentence.find(" ", start)) != string::npos){
        // reverse the current word
        reverse(sentence.begin() + start, sentence.begin() + end_pos);
        // index after space for the next word start pos.
        start = end_pos + 1;
    }
    //reverse the last word
    reverse(sentence.begin() + start, sentence.end());
    // reverse the entire string
    reverse(sentence.begin(), sentence.end());

    return sentence;
}

int main(){
    cout << reverseWordsSentence("Coding and gaming") << endl <<
        reverseWordsSentence("Anna likes Bob") << endl;
    return 0;
}
