/*
    Given a tree. Do preorder traversal without recursion.

    Solution:
        We use stack for imitating the recursive calls.

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

// preorder traversal without recursion
void iterativePreorderTraversal(unique_ptr<Node<int>>& root) {
    stack<Node<int>*> s;
    Node<int>* curr = root.get();

    // since it is preorder, we print as we go as much left as possible
    // and then go right, else go to the parent
    while (curr || !s.empty()) {
        // go left 
        if (curr) {
            s.push(curr);
            // print the current data
            cout << curr->data << " ";
            curr = curr->left.get();
        }
        else {
            // when going left is not possible
            curr = s.top();
            s.pop();
            // go right
            curr = curr->right.get();
        }
    }
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
    iterativePreorderTraversal(root);
    return 0;
}