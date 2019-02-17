/*
    Given a binary tree and a sum, find if any root to 
    leaf path contains that sum.

    Solution:
        We can do any DFS traversal and during going 
        down the level, we just pass the current_sum - curr_data,
        when on reaching the leaf node if the sum is 0, then the path is found.
        TC: O(n)
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

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

// checks if there is any root to leaf path with given sum
bool isSumPathPossible(unique_ptr<Node<int>>& root, int sum) {
    if (!root)
        return false;

    // update the sum
    sum = sum - root->data;

    // if the current node is a leaf and sum is 0
    if (!root->left && !root->right && !sum)
        return true;
    // traverse the rest of the tree
    return isSumPathPossible(root->left, sum) ||
        isSumPathPossible(root->right, sum);
}

struct SumData {
    int sum;
    Node<int>* node;
};

// does same as above, but iteratively
bool isSumPathPossibleIteratively(unique_ptr<Node<int>>& root, int sum) {
    // here we use inorder traversal
    stack<SumData> s;
    SumData curr = { sum, root.get() };

    while (!s.empty() || curr.node) {
        // go left
        if (curr.node) {
            // update sum value for current
            curr.sum = curr.sum - curr.node->data;
            s.push(curr);
            // update node ptr 
            curr.node = curr.node->left.get();
        }
        else {
            curr = s.top();
            s.pop();
            // if a path is found
            if (!curr.node->left && !curr.node->right && !curr.sum) {
                return true;
            }
            curr.node = curr.node->right.get();
        }
    }

    return false;
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
   // postOrderTraversal(root);
    cout << endl;
    cout << isSumPathPossible(root, 17);
    cout << endl << isSumPathPossibleIteratively(root, 17);
    return 0;
}