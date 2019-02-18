/*
    Given a binary tree and a tree node. Find the inorder successor of 
    the node.

    Solution:
        In inorder traversal, we first go to left subtree, current and then
        right subtree. So for the given node, if the right subtree is present
        then the successor is the leftmost node in that subtree.
        If the right subtree is not present, then the inorder successor
        is the first node whose left subtree contains this node.

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

// finds the inorder successor of a given node
Node<int>* findSuccessor(unique_ptr<Node<int>>& root, 
                            unique_ptr<Node<int>>& node) {
    Node<int>* curr = nullptr;

    // check if the current node has a right subtree or not
    if(node->right.get() != nullptr) {
        // go to the left most node
        curr = node->right.get();
        while(curr->left) {
            curr = curr->left.get();
        }
        return curr;
    }
    
    // if there is no right subtree, then successor is the
    // first node whose left subtree contains given node
    curr = node.get();
    // climb up untill you find that current is part of left subtree
    while(curr->parent && curr != curr->parent->left.get()) {
    	curr = curr->parent;
    }
    
    return curr->parent;
}

// inorder traversal
template<typename T>
void inOrderTraversal(unique_ptr<Node<T>>& root) {
    if (root) {
        inOrderTraversal(root->left);
        inOrderTraversal(root->right);
        cout << root->data << " ";
    }
}

int main() {
    /*
                    1
                  /   \
                2      3
               /  \   /
              4    5  6
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
    root->left->right->parent = root->right.get();

    root->right->left = make_unique<Node<int>>(6);
    root->right->left->parent = root->right.get();
    
    root->right->left->left = make_unique<Node<int>>(7);
    root->right->left->left->parent = root->right->left.get();

    inOrderTraversal(root);
    cout << endl;
    auto result = findSuccessor(root, root->right);
    if(result)
    	cout << result->data << endl;
    else
    	cout << "No successor\n";
    return 0;
}
