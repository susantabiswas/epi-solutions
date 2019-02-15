/*
    Problem:
        Given a positive number represented as array of digits, add 1 to the number
    
    Input: int array
    Output: int array
    
    Solution:
        Start traversal from last index and add 1 to it, then propagate the carry if there to the left 
        side digits.

        TC: O(n)
        SC: O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// adds 1 to array based number
vector<int> incrementNumber(vector<int> arr) {
    // stores the incremented number
    vector<int> result = arr;
    int carry = 0;

    // add the last digit
    result[arr.size() - 1] = result[arr.size() - 1] + 1;

    // start from the last digit
    for(int i = arr.size() - 1; i >= 0; i--) {
        // add carry if there 
        result[i] += carry;
        // set carry if there
        carry = result[i] / 10;
        result[i] %= 10;
    }

    // add the carry if still there
    if(carry) {
        result.insert(result.begin(), carry);
    }
    return result;
}

ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr) 
        cout << a << " ";
    cout << endl;
}

int main(){
    vector<int> arr = {9,9,9,9,9,9,9};

    cout << incrementNumber(arr);
    return 0;
}
