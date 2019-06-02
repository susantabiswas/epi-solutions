/*
    Buy and sell stock twice:
        Given an array of numbers which represent the stock prices for a day. Find the 
        max gain that can be made by buying a stock and selling that and again doing the same.
	The second stock can be bought only when the first is sold.

    Soltuion:
        The gain will be made when the difference between sold and bought stock is maximum. So we need
        to find the max diff for eack price. But since here we buy another stock after first is sold, so
        for each price we store the max gain that can be made till that price, either by selling at that
        price or if already sold before that price. Next we check the gain that can be made for each price if stock is bought 
        at that price and sold later.
        we need to track two things:
        for a given price 'i':
        1. max gain made if bought stock is sold at that price or before
        2. max gain made if stock is bought at this price and sold later: this is the max price that occurs after 
            this price. 
        We save the results for 1 and do one more traversal to see which price is giving the max gain

        TC: O(n)
        Sc: O(n), for saving the gain results from buying stock once
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the max gain for buying stock once and selling in that day itself twice
int maximizeBuyTwiceStockProfit(vector<int>& prices) {
    int max_profit = 0;
    int curr_gain = 0;
    int min_till_this = 0;
    int max_after_this = prices.size() - 1;
    
    // each ith entry stores the max gain if the stock is sold at that price
    vector<int> gain_if_stock_sold(prices.size(), 0);
    
    // forward pass: to find the max gain for selling at each ith price
    for(int i = 0; i < prices.size(); i++) {
        // check if the current stock price is min, if this is updated then
        // if the current is min so far, diff will be negative and misleading
        min_till_this = prices[min_till_this] > prices[i] ? i : min_till_this;
		
        // compute the diff with the min price seen so far
        curr_gain = prices[i] - prices[min_till_this];
        // set the highest gain that can be made till this price
        max_profit = max(curr_gain, max_profit);
        gain_if_stock_sold[i] = max_profit;
        
    }
	
	max_profit = 0;
    // backward pass: to find the max gain if stock is bought at each ith price and sold later
    for(int i = prices.size() - 1; i >= 0; i--) {
        // update current max
        max_after_this = prices[max_after_this] < prices[i] ? i : max_after_this;

        // find the profit made if current stock is bought and sold later
        curr_gain = prices[max_after_this] - prices[i];
        // check if max gain can be made if stock is sold at current price and bought at this
        // price for selling later
        max_profit = max(max_profit, curr_gain + gain_if_stock_sold[i]);
    }
	
    return max_profit;
}

int main() {
    vector<int> prices = {12, 11, 13, 9, 12, 8, 14, 13, 15};
    cout << maximizeBuyTwiceStockProfit(prices);
    return 0;
}
