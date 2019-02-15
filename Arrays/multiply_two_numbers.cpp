/*
    Problem:
        Given two int numbers in array form, multiply them and give the result in array form only. 
    
    Input: int array, int array
    Output: result array
    
    Solution:
        We do the product using the normal multiplication method we do on paper. 
        Start with the end of both the arrays and start multiplying the digits of
        number 1 with digit of number 2.
    
        TC: O(nm), n: no. of digits of number 1, m: no. of digits of number 2
        SC: O(n + m)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> multiplyNumbers(vector<int>& a, vector<int>& b) {
    // check if the product will be negative or not
    bool is_negative = a.front() * b.front() >= 0 ? false : true; 
    // remove the sign from the front
    a.front() = abs(a.front());
    b.front() = abs(b.front());

    // stores multiplication result
    vector<int> result(a.size() + b.size(), 0);

    // number 'b' will multiply number 'a'
    for(int i = b.size() - 1; i >= 0; i--) {
        for(int j = a.size() - 1; j >= 0; j--) {
            result[i + j + 1] += a[j] * b[i];
            // add the carry with the next digit
            result[i + j] += result[i + j + 1] / 10;
            // have the last digit of the product only 
            result[i + j + 1] %= 10;
        }
    }


    // since there can be unused places in result vector filled with zero, remove them
    result = vector<int>{find_if_not(result.begin(), result.end(), [](int digit){
                                    return !digit;    // return false for the first non-zero digit
                            }), result.end()}; 
    // set the sign if any
    result.front() = is_negative ? -1 * result.front() : result.front();
    return result;
}


ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr) 
        cout << a << " ";
    cout << endl;
}

int main(){
    vector<int> b = {4, 2, 3, 7, 0, 7, 7, 2, 1, 3, 1, 2};
    vector<int> a = {-2, 6, 1, 3, 3, 1, 2, 1, 7, 2, 8, 7};

    cout << multiplyNumbers(a, b);
    return 0;
}
