/*
    Problem:
        Given a text t, print it in sinusoidally fashion
        e.g: "mynameis"
          y       e
        m   n   m   i
              a      s

    Input:
        t: string

    Output:
        Nothing just print the text

    TC: O(n), n: no. of chars
*/

#include<iostream>
#include<vector>
using namespace std;

// prints the string in sinusoidally fashion
/*
    There are three rows involved in the printing. Also each row has
    only has indices with a fixed constant difference.
    e.g: "mynameis"
          y       e
        m   n   m   i
              a      s

        row 1: 1, 5
        row 2: 0, 2, 4, 6
        row 3: 3, 7
*/
void printSinusoidally(const string& str){
    // print the indices at 1, 5 .. positions
    for(int i = 1; i < str.size(); i += 4){
        cout << " " << str[i];
        // each char is separated by three spaces
        for(size_t j = 0; j < 2; j++)
            cout << " ";
    }

    cout << endl; 

    // print the indices at 0, 2 .. positions
    for(int i = 0; i < str.size(); i += 2){
        cout << str[i];
        // each char is separated by 1 space
        for(size_t j = 0; j < 1; j++)
            cout << " " ;
    }

    cout << endl;

    // print the indices at 3, 7 .. positions
    for(int i = 3; i < str.size(); i += 4){
        // each char preceeded by three spaces
        cout << "   " << str[i];
    }   
}

int main(){
    printSinusoidally("abcdefghijklmnopqrstuvwxyz");    
    return 0;
}