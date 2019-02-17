/*
    Given a tree with binary digit as data. Root represents MSB and leaf
    represent LSB. So each root to leaf path forms one number. Find the sum of all
    the numbers which can be formed from root to leafs.

    Solution:
        For converting a binary number to decimal, we multiply by its
        place value 2. So starting from root if we multiply the number formed
        till that level by 2 and adding the digit of current node, we get
        the complete number by the time we reach the leaf node.

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

int rootToLeafSum(unique_ptr<Node<int>>& root, int sum) {
    if (!root)
        return 0;

    // multiply the sum value by 2 and add the current digit
    sum = sum * 2 + root->data;

    // if the current is leaf, then return the sum
    if (!root->left && !root->right)
        return sum;

    return rootToLeafSum(root->left, sum) + 
            rootToLeafSum(root->right, sum);
}

// finds the sum of all root to leaf paths
int findRootToLeafSum(unique_ptr<Node<int>>& root) {
    return rootToLeafSum(root, 0);
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
                0      1
               /  \   /
              0    1  1
                     /
                    0
    */
    unique_ptr<Node<int>> root = make_unique<Node<int>>(1);
    root->left = make_unique<Node<int>>(0);
    root->right = make_unique<Node<int>>(1);
    root->left->left = make_unique<Node<int>>(0);
    root->left->right = make_unique<Node<int>>(1);

    root->right->left = make_unique<Node<int>>(1);
    root->right->left->left = make_unique<Node<int>>(0);
    postOrderTraversal(root);
    cout << endl;
    cout << findRootToLeafSum(root);
    return 0;
}