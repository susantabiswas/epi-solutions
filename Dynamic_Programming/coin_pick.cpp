/*
    Given an array of int, where each entry represent value of a coin. There are two players
    and they are playing a game, where in each turn they select a coin either from front or
    back of the array, the player who ends up the largest sum of coin values once 
    all the coins have been picked wins. Find the largest value coins that can be
    collected if a player starts first, assume that the second player is trying his best at each turn also. 

    Solution:
        TC:
        SC:
*/

#include <iostream>
#include <vector>
using namespace std;
                                                             
int main() {
    vector<int> coins = {};

    cout << maximizeCoinValue(coins);
    return 0;
}
