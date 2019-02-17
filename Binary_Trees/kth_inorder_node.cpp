/*
    Given a binary tree, where the nodes contains additional info about
    the no. of nodes in its subtree. Find the Kth node in inorder traversal
    of this tree.

    Solution:
        Since each root of a subtree has info about the no. of nodes in 
        its subchild, we can us that info to decide in which direction to go.
        For current root:
        if num_child in left subtree is < K: then it is definitely not in left
        if num_child in left + 1 == K, then it is root
        if num_child in left > K: go left
        if num_child in left + 1 < K: go right

        TC: O(h), since at max we will go to one leaf node
        Sc: O(h), for recursive stack
*/

#include <iostream>
#include <algorithm>
#include <memory>
#include <stack>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;
    int num_nodes;
    Node(T data) : data(data), left(nullptr), right(nullptr),
                    num_nodes(0) {}
};

// finds the kth node in inorder traversal of tree
Node<int>* findKthInorderNode(unique_ptr<Node<int>>& root, int k) {
    // start with root
    Node<int>* curr = root.get();

    while (curr) {
        int left_nodes = curr->left ? curr->left->num_nodes : 0;
        int right_nodes = curr->right ? curr->right->num_nodes : 0;

        // now compare with K
        // when it is in left subtree
        if (left_nodes >= k) {
            curr = curr->left.get();
        }
        // when it is the root
        else if (left_nodes + 1 == k) {
            return root.get();
        }
        // either it is on right or K is more than total nodes
        else {
            k = k - (left_nodes + 1);
            curr = curr->right.get();
        }
    }
    cout << "Not found";
    return nullptr;
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
                  /   \
                2      3
               /  \   /
              4    5  6
                     /
                    7
    */
    unique_ptr<Node<int>> root = make_unique<Node<int>>(1);
    root->num_nodes = 7;

    root->left = make_unique<Node<int>>(2);
    root->left->num_nodes = 3;

    root->right = make_unique<Node<int>>(3);
    root->right->num_nodes = 3;

    root->left->left = make_unique<Node<int>>(4);
    root->left->left->num_nodes = 1;

    root->left->right = make_unique<Node<int>>(5);
    root->left->right->num_nodes = 1;

    root->right->left = make_unique<Node<int>>(6);
    root->right->left->num_nodes = 2;

    root->right->left->left = make_unique<Node<int>>(7);
    root->right->left->left->num_nodes = 1;

    inOrderTraversal(root);
    auto result = (findKthInorderNode(root, 17));
    if(result)
        cout << endl << result->data << endl;
    return 0;
}