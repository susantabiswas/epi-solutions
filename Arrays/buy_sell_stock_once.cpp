/*
    Buy and sell stock once:
        Given an array of numbers which represent the stock prices for a day. Find the 
        max gain that can be made by buying a stock and selling that day itself.

    Soltuion:
        The gain will be made when the difference between sold and bought stock is maximum. So we need
        to find the max diff for eack price. Basically for each price
        the maximum gain that can be made if sold at that price is when we buy the stock at price which 
        is min seen till that price. We compute this for each price and track the maximum diff.
        TC: O(n)
        Sc: O(1)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the max gain for buying stock once and selling in that day itself
int maximizeBuyOnceStockProfit(vector<int>& prices) {
    int max_profit = 0;
    int curr_diff = 0;
    int min_till_this = 0;
    
    for(int i = 0; i < prices.size(); i++) {
        // check if the current stock price is min, if this is updated then
        // if the current is min so far, diff will be negative and misleading
        min_till_this = prices[min_till_this] > prices[i] ? i : min_till_this;
        // compute the diff with the min price seen so far
        curr_diff = prices[i] - prices[min_till_this];
        max_profit = max(max_profit, curr_diff);
    }
    return max_profit;
}

int main() {
    vector<int> prices = {311, 315, 275, 295, 2320, 271, 290, 240, 255, 210};
    cout << maximizeBuyOnceStockProfit(prices);
    return 0;
}
