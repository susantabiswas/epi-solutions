/*
    Check if a tree is height balanced or not.
    Tree is height balanced if the height diff between left and right subtree is
    max 1.

    Solution:
        We do a postorder traversal and while going up check for the 
        height diff of each descendent subtree. If the diff is more than 1, 
        return false.

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

struct HeightInfo {
    bool balanced;
    int height;
};

template<typename T>
HeightInfo checkHeightBalanced(unique_ptr<Node<T>>& root) {
    // if the node is null
    if (!root)
        return { true, -1 };
    
    // left subtree
    auto left = checkHeightBalanced(root->left);
    // check if the left subtree is balanced 
    if (left.balanced == false)
        return { false, 0 };

    // right subtree
    auto right = checkHeightBalanced(root->right);
    // check if right subtree is balanced
    if (right.balanced == false)
        return { false, 0 };
    // compute the height diff between left and right subtree
    bool is_balanced = (abs(left.height - right.height) <= 1);
    // height of parent node
    int parent_height = max(left.height, right.height) + 1;

    return {is_balanced, parent_height};
}

// checks if the tree is height balanced or not
template<typename T>
bool isHeightBalanced(unique_ptr<Node<T>>& root) {
    return checkHeightBalanced(root).balanced;
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
    cout << isHeightBalanced(root);
    return 0;
}