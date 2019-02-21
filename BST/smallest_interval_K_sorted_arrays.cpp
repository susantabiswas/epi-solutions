/*
    Given K sorted arrays, select one element from each array such that the interval diff.
    for those K elements is min.
    Eg: Suppose result is {22, 3, 9, 89} : Here interval is [22, 89] for K diff arrays
    
    Solution:
        The idea behind having a small interval is to have the min diff for max and min number amongst those K elements.    
        Initially we start with the first elements of each of the K arrays, we want to have the upper and lower limits to be close to each
        other, so we start with the smallest values each array has to offer.

        While none of the arrays is finished:
            
            1.pick the min amongst K and compute interval diff, then remove it
            2. min_diff = min(min_diff, current interval diff)
            3. take the next element from the array the min element belonged to and add it to K array

            4. if(the array from which element was picked has no element, exit)

        NOTE: We stop once an array is finished, because it means that the lower limit is currently is the last element from the
            array which got finished and the remaining values in K array are greater than that value. So we cannot make the diff between 
            our upper and lower limits smaller, since the min element won't change and the other array's remaining values are greater than the current upper 
            limit, so the diff will only grow.

        Since the solution involves finding the min each time, we can use a BST for this. The insertion, deletion and finding min 
        will be better.

        TC: O(nlogk), n: total number of elements
        SC: O(k) 
*/
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <utility>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;

    Node(T data): data(data), left(nullptr), right(nullptr) {}
};

// finds the smallest interval difference for K elements
int findKSmallestInterval(vector<vector<int>>& arr) {
    struct IteratorInfo {
        vector<int>::iterator curr;
        vector<int>::iterator tail;
    };
    
    // each entry is <data, current iterator and end iterator for current vector>
    multimap<int, IteratorInfo> k_interval;

    // start with the first element of each of the K arrays
    for(int i = 0; i < arr.size(); i++) {
        k_interval.emplace(arr[i][0], IteratorInfo{arr[i].begin(), arr[i].end()});
    }

    int min_diff = numeric_limits<int> :: max();
    // everytime we pick the smallest amongst K and try to replace it with the next larger element 
    // as the lower limit
    while(true) {
        // finds the min and max
        int lower_limit = k_interval.cbegin()->first;
        int upper_limit = k_interval.crbegin()->first;

        // compute the interval diff
        min_diff = min(min_diff, upper_limit - lower_limit);

        // update the lower limit with next element of array from which lower limit belongs
        auto next_min_iter = next(k_interval.cbegin()->second.curr);
        auto next_end_iter = k_interval.cbegin()->second.tail;

        // if the array has no more elements exit
        if(next_min_iter == next_end_iter)
            return min_diff;

        // remove the current lower limit
        k_interval.erase(lower_limit);
        // add the next element from that array
        k_interval.emplace(*next_min_iter, IteratorInfo{next_min_iter, next_end_iter});
    }
}

// inorder traversal
template<typename T>
void inOrderTraversal(Node<T>* iter) {
    if (iter) {
        inOrderTraversal(iter->left.get());
        cout << iter->data << " " ;
        inOrderTraversal(iter->right.get());
    }
}

int main() {
    vector<vector<int>> arr = {
    	{5,10,15},
    	{3,6,9,12,15},
    	{8, 16, 24}
    };
    cout << findKSmallestInterval(arr);
    
    return 0;
}    
