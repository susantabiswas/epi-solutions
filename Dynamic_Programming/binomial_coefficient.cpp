/*
    Given 'n' and 'k'. Compute the binomial coefficient,
    
    Input: int, int
    Output: int
    
    Solution:
        The formula for (n, k) =  n! / (n-k)! k!
        But if we computing the factorial might give us overflow, since the
        numerator and denominator both might reach values that can be stored in 32bit int.

        There is another way for (n, k).
        (n, k) = (n-1, k) + (n-1, k-1)
        this is a recursive formula, which can prevent overflow. We use a cache for storing the
        intermediate values.

        Base case will be when (k, k) or when k = 0, both are 1
        TC: O(nk)
        SC: O(nk)
*/

#include <iostream>
#include <vector>
using namespace std;

int findBinomialCoefficientHelper(int n, int k, vector<vector<int>>& coefficient) {
    // base case
    if(k == 0 || n == k)
        return 1;

    if(coefficient[n][k] == 0) {
        coefficient[n][k] = findBinomialCoefficientHelper(n - 1, k, coefficient) +
                            findBinomialCoefficientHelper(n - 1, k - 1, coefficient);
    }
    return coefficient[n][k];
}

// finds the binomial coefficient 
int computeBinomialCoefficient(int n, int k) {
    // each (n,k) entry stores the binomial coefficient for that
    vector<vector<int>> coefficient(n+1, vector<int>(k+1, 0));

    return findBinomialCoefficientHelper(n, k, coefficient);
}

int main() {
    int n = 5;
    int k = 5;

    cout << computeBinomialCoefficient(n, k);
    return 0;
}
