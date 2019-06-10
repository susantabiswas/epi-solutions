/*
    Problem:
        Look and Say problem: We need to find the nth term in look and say series.
        The series starts with 1 and each next term is formed by looking at the previous:
        no of digits + digit ...
        Eg: 1, one 1, two 1, one 2 one 1
            1, 11, 21, 1211, 11, 1221

    Input:
        n: int

    Output:
        nth string term
        
    TC:
        T(n) <= 2*T(n-1),
                ~ 2^n
        Each ith term can have at max twice the number of chars that (i-1)th term
        had. Also for finding nth term, we need to find the terms from 1...n.
        Total: O(n * 2^n)
*/

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

//displays the series
void displaySeries(vector<string>& series){
    for(string term: series)
        cout << term << endl;
    cout << endl;
}

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

// finds the term using the previous term
string lookAndSayTerm(string prev_term){
    // scan for consecutive same digits and keep their counts
    int count_digit = 1;
    string term;

    for(int i = 0; i < prev_term.size(); i++){
        // if the current char is different from previous
        // then write the char with its count
        while( i+1 < prev_term.size() && prev_term[i] == prev_term[i+1]){
            ++count_digit;
            ++i;
        }
        term += to_string(count_digit) + prev_term[i];
        count_digit = 1;
    }
    return term;
}

// finds the nth term in look and say series
string nthLookSayTerm(int n){
    // to store the series
    vector<string> series;
    // first term
    series.push_back("1");

    for(int i = 1; i< n; i++){
        // finds the term using the previous term
        series.push_back(lookAndSayTerm(series.back()));
    }
    displaySeries(series);
    cout << endl;
    return series.back();
}

int main(){
    cout << nthLookSayTerm(7);
    return 0;
}
