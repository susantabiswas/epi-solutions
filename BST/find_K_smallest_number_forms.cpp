/*
    Given K, find the smallest k numbers of the form a + b*Root(2),
    where a, b: non-neg int.
    General form : a + b*Root(q), q: irrational number and a,b : non-neg int
    
    Solution:
        Since 'a' and 'b' can have only int values, that means first two min values are:
        0 + 0*Root(2), then next is 1 + 0*Root(2), 0 + 1*Root(2).
        To make sure the next value generated is min, we increase 'a' and 'b' by 1.
        We use a BST of size k, every time we extract the min from it and then push
        two values, one with (a + 1, b) and (a, b+1)
        TC: O(klogk),k extractions in BST. Each extraction takes O(logk) in BST of size k.
        SC:  O(k)
*/
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <limits>
#include <utility>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;

    Node(T data): data(data), left(nullptr), right(nullptr) {}
};

struct NumberForm {
    int a, b;
    double value;

    NumberForm(int a, int b) : a(a), b(b), value(a + b * sqrt(2)) {};
    bool operator<(const NumberForm& b) const {
        return value < b.value;
    } 
};

// finds the K smallest numbers of form a + b * Root(2)
vector<NumberForm> findKSmallestNumbers(int k) {
    set<NumberForm> candidates;
    vector<NumberForm> result;

    // we initialise the BST with a = 0, b = 0
    candidates.emplace(NumberForm(0, 0));
	// find the k smallst such numbers
    while(k--) {
        auto smallest = candidates.cbegin();
        // add it to the result
        result.emplace_back(*smallest);
        // add the next two numbers
        candidates.emplace(NumberForm{smallest->a + 1, smallest->b});
        candidates.emplace(NumberForm{smallest->a, smallest->b + 1});
        
        // remove the smallest  
        candidates.erase(smallest);
    }
    
    return result;
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

    auto result = findKSmallestNumbers(5);
    for(const auto& a: result) {
    	cout << a.a << " + " << a.b << " * Root(2) : " << a.value << endl; 
    }
    
    return 0;
}    
