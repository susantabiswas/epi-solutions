/*
    Given a binary tree and a value K, find the K largest elements.
    
    Solution:

        TC: 
        SC: 
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

// finds the k largest elements 
vector<Node<int>*> findKLargestElements(unique_ptr<Node<int>>& root, int k) {

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
    
    auto result = findKLargestElements(root, 3);
    return 0;
}
