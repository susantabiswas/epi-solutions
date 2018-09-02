/*
    Problem:
        Rabin Karp Algo

    Input:
        patt: string pattern
        text: string text   

    Output:
        matched indices: vector of indices
    
    TC: Avg case: O(m + n)
        Worst case: O(mn)
        m: length of pattern
        n; legth of text 
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
    The idea behind Rabin Karp is we use a hash function to compute the
    hash value of the pattern and text window. When the hash value of the
    window matches that of the pattern, then we check if the pattern is actually
    present or not. 
*/
vector<int> rabinKarp(string& text, string& patt){

    // base for the 26 alphabatical chars
    int base = 26; 
    // base ^ length of (pattern)
    long int power_patt = 0;
    // length of the pattern
    int M = patt.length();
    // length of txt
    int N = text.length();
    // hash value of pattern
    int hash_patt = 0;
    // hash value of text
    int hash_text = 0;
    // number for doing the mod
    int q = 101;
    // for storing the matched indices
    vector<int> indices;

    // find the hash value of the pattern and the first window of text
    for(int i = 0; i < M; i++){
        power_patt *= base;
        hash_patt = (hash_patt * base + patt[i]) % q;
        hash_text = (hash_text * base + text[i]) % q;
    }

    // traverse through the text using the window
    for(int i = 1; i <= N - M; i++){
        // check if the hash values match
        if(hash_patt == hash_text){
            // check if it actually matches
            if(text.compare(i, M, patt) == 0)
                indices.emplace_back(i);
        }

        // adjust the hash value for the new window
        hash_patt = hash_patt - (power_patt * text[i-1] % q);
        hash_patt = hash_patt * base + text[i] % q;
    }


}

int main(){
    
    return 0;
}