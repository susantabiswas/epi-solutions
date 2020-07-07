/*
    Given a binary search tree and two nodes, find the LCA.
    
    Solution:
        For a binary tree it can be done in O(n) in worst case. For BST, we can do better.
        We can prune our search in BST.
        For a given node:
        1. If the root is either of 'a' or 'b', then it is the LCA.
        2. If the root is such that both 'a' and 'b' lie on the opposite subtrees, then it is the
            LCA.
        3. If the root is lesser than both 'a' and 'b', LCA is in right subtree.
        4. If the root is greater than both 'a' and 'b', LCA is in left subtree.

        TC: worst-case: O(n) skewed tree, Avg. Case: O(h)
        SC: O(h)
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

// finds the LCA of two nodes in BST
Node<int>* findLCAinBST(unique_ptr<Node<int>>& root, unique_ptr<Node<int>>& a,
                            unique_ptr<Node<int>>& b) {
    // if we reach reach the first null node, then that means there is no LCA
    // since we have been prunning the search acc. to the two nodes, so thereis no
    // chance that there is a LCA if we have reached the null ptr
    if(!root)
        return nullptr;
    // check if the node is one of 'a' or 'b'
    // this will be the LCA, since we have reached it first in BST
    if(root.get() == a.get() || root.get() == b.get())
        return root.get() == a.get() ? a.get() : b.get();
        
    else if((root->data > a->data && root->data < b->data) ||	// when the nodes lie on different subtrees
        (root->data < a->data && root->data > b->data))
        return root.get();

    else if(root->data < a->data && root->data < b->data)   // when both are smaller
        return findLCAinBST(root->right, a, b);
    else                                                    // when both are larger
        return findLCAinBST(root->left, a, b);
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
    // 8 and 7
    auto lca = findLCAinBST(root,  root->right, root->right->left);
    cout << endl << lca->data << endl;
    return 0;
}
