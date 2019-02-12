/*
    Given a knapsack which has a weight limit and arrays of costs
    and weights for objects. Maximize the value of knapsack by filling it
    with objects.

    Solution:
        For each object:
            that object can be included:
                if the weight exceeds the capacity go for the next object
            the object can be excluded:
        TC: O(ns), n: no. of items and s: knapsack weight
        SC: O(ns)
*/

#include <iostream>
#include <vector>
using namespace std;

struct Item {
    int weight;
    int value;
};

int maximumKnapsackValue(vector<Item>& arr, int n, int s, vector<vector<int>>& cache) {
    // if there are no items left
    if(n <= 0)
        return 0;

    if(cache[n-1][s] == -1) {
        // we can either include current item or exclude it
        int include_item = arr[n-1].weight <= s ? 
                            arr[n-1].value + maximumKnapsackValue(arr, n-1, s - arr[n-1].weight, cache) 
                            : 0;
        int exclude_item = maximumKnapsackValue(arr, n-1, s, cache);

        cache[n-1][s] = max(include_item, exclude_item);
    }
    return cache[n-1][s];
}

// maximizes the knapsack value
int optimumKnapsackValue(vector<Item>& arr, int s) {
    // each entry (i, j) is the optimum knapsack value when the
    // max weight can be 'j' and there are 'i' items
    vector<vector<int>> cache(arr.size(), vector<int>(s+1, -1));
    return maximumKnapsackValue(arr, arr.size(), s, cache);
}

int main() {
    vector<Item> arr = {{10, 60}, {20, 100}, {30, 120}};
    int s = 50;

    cout << optimumKnapsackValue(arr, s);
    return 0;
}
