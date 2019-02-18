/*
    Given a binary tree where the nodes have parent link. Implement
    inorder traversal with O(1) space.

    Solution:
        In inorder traversal, we first go to left subtree, current and then
        right subtree. 
        Main problem is to not print a node twice. This depends how we reach a node, whether from
        left or right subtree.
        There can be following situtaions:
        1. Going down: Then once we reach a leaf, print it and start going up
        2. Going up: If came from left, print current else if 
        came from right, go up

        TC: O(n)
        Sc: O(h), for recursive stack
*/
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* parent; // I am not writing unique ptr for this, only because there is too much code 
                    // to write in the main body for that. But this should also be unique_ptr
    unique_ptr<Node<T>> left, right;
    
    Node(T data) : data(data), left(nullptr), right(nullptr),
                    parent(nullptr) {}
};

// inorder traversal with const space
void inOrderTraversalConstantSpace(unique_ptr<Node<int>>& root) {
    if(!root)
        return;
    // start with the root node
    Node<int>* curr = root.get();
    Node<int>* prev = nullptr;  // keeping track of previous node
    Node<int>* next = nullptr; // keeps track of next node to go
    
    while(curr != nullptr) {
        // while going down the tree
        if(prev == curr->parent) {
            // if the left subtree is there
            if(curr->left) {
                next = curr->left.get();
            }
            else {  // when we hit a leaf node or when the left subtree is not
                    // there, but right subtree might be there
                // print current node
                cout << curr->data << " ";
                // if the right subtree is there, then go right or climb up
                next = curr->right ?  curr->right.get() : curr->parent;
            }
        }
        // if going up from left side
        else if(curr->left.get() == prev) {
            // print current node and go right if possible
            cout << curr->data << " ";
            next = curr->right ? curr->right.get() : curr->parent;
        }
        else {  // going up from right side
            next = curr->parent;
        }

        prev = curr;
        curr = next;
    }
}

// inorder traversal
template<typename T>
void inOrderTraversal(unique_ptr<Node<T>>& root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
    	inOrderTraversal(root->right);
    }
}

int main() {
    /*
                     1
                  /    \
                 2      3
                / \    /
               4   5  6
                     /
                    7
    */
    unique_ptr<Node<int>> root = make_unique<Node<int>>(1);
    root->parent = nullptr;
    
    root->left = make_unique<Node<int>>(2);
    root->left->parent = root.get();

    root->right = make_unique<Node<int>>(3);
    root->right->parent = root.get();
    
    root->left->left = make_unique<Node<int>>(4);
    root->left->left->parent = root->left.get();
    
    root->left->right = make_unique<Node<int>>(5);
    root->left->right->parent = root->left.get();

    root->right->left = make_unique<Node<int>>(6);
    root->right->left->parent = root->right.get();
    
    root->right->left->left = make_unique<Node<int>>(7);
    root->right->left->left->parent = root->right->left.get();

    inOrderTraversal(root);
    cout << endl;
    inOrderTraversalConstantSpace(root);
    return 0;
}
