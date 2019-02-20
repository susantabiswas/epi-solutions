/*
    Given a binary tree and a key, find the first node whose data value is greater than the key.
    
    Solution:
        Do normal BST search till we get a node > key. Then we find the smallest in its left subtree

        TC: O(n)
        SC: DFS: O(logn), for n sized array
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

// finds the element just greater than given key
Node<int>* findJustGreaterNode(unique_ptr<Node<int>>& root, int key) {
    if(!root)
        return nullptr;
    // keeps track of last seen greater element
    Node<int>* just_greater = nullptr;
    Node<int>* curr = root.get();
    // traverse till we get the first larger element or when the nodes end
    while(curr) {
        // if a greater node is found
        if(curr->data > key) {
            just_greater = curr;
            curr = curr->left.get();
        }
        else {  // when current node is smaller, go right
            curr = curr->right.get();
        }
    }
    return just_greater;
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
    cout << endl << (findJustGreaterNode(root, 2))->data << endl;
    return 0;
}
