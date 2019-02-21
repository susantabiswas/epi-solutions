/*
    Given a BST and a value K, find the K largest elements.
    
    Solution:
        We start the traversal with right, root and then left approach. This way we will get to the rightmost,
        then we fallback to the next largest. We do this till k elements have been added.
        TC: O(h + k), since we go to the deepest leaf on right, then ascend upwards k times
        SC: O(h)
*/
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;

    Node(T data): data(data), left(nullptr), right(nullptr) {}
};

void findKLargestElementsHelper(unique_ptr<Node<int>>& root, int& k, 
                                        vector<int>& result) {
    if(!root)
        return;

    if(k > 0) {
	    /*
	        We will first hit the rightmost node which is the largest, then the next one will come once
	        we recurse back and go to the next successor.Like inorder successor gives ascending sequence, 
	        same way we are just doign inorder from reverse side so we get descending sequence.
	    */
	    findKLargestElementsHelper(root->right, k, result);
	    if(k > 0) {
	    	--k;
		    result.emplace_back(root->data);
		}
	    findKLargestElementsHelper(root->left, k, result);
    }
}

// finds the k largest elements 
vector<int> findKLargestElements(unique_ptr<Node<int>>& root, int k) {
    // for storing the k largest elements
    vector<int> result;
    findKLargestElementsHelper(root, k, result);
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
    /*
                    5
                  /   \
                2      8
               /  \   /  \
              1    3  7   9
                     /
                    6
    */
    unique_ptr<Node<int>> root = make_unique<Node<int>>(5);
    
    root->left = make_unique<Node<int>>(2);
    root->right = make_unique<Node<int>>(8);

    root->left->left = make_unique<Node<int>>(1);
    root->left->right = make_unique<Node<int>>(3);

    root->right->left = make_unique<Node<int>>(7);
    root->right->left->left = make_unique<Node<int>>(6);

    root->right->right = make_unique<Node<int>>(9);

    inOrderTraversal(root.get());
    cout << endl;
    auto result = findKLargestElements(root, 2);
    for(const auto& a: result)
        cout << a << " ";
    return 0;
}
