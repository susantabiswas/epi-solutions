/*
    Check if tree is symmetric about root.

    Solution:
        Start simultaneous traversal of left and right subtrees, if the
        tree is symmetric , then the left and right subtree values will always
        be equal.

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
    unique_ptr<Node<T>> left, right;
    
    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

bool checkTreeSymmetry(unique_ptr<Node<int>>& node1,
    unique_ptr<Node<int>>& node2) {
    
    // if both the nodes are null
    if (node1 == nullptr && node2 == nullptr)
        return true;
    // if only one of them is null, then symmetry breaks
    if ((!node1 && node2) || (node1 && !node2))
        return false;

    return (node1->data == node2->data) &&
        checkTreeSymmetry(node1->left, node2->right) &&
        checkTreeSymmetry(node1->right, node2->left);
}

// checks if the given tree is symmetric about root
bool isSymmetric(unique_ptr<Node<int>>& root) {
    return checkTreeSymmetry(root->left, root->right);
}

// postorder traversal
template<typename T>
void postOrderTraversal(unique_ptr<Node<T>>& root) {
    if (root) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
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
    root->left = make_unique<Node<int>>(2);
    root->right = make_unique<Node<int>>(3);
    root->left->left = make_unique<Node<int>>(4);
    root->left->right = make_unique<Node<int>>(5);

    root->right->left = make_unique<Node<int>>(6);
    root->right->left->left = make_unique<Node<int>>(7);

    postOrderTraversal(root);
    cout << endl;
    cout << isSymmetric(root);
    return 0;
}