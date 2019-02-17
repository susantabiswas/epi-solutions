/*
    Given two tree nodes with parent pointers, find the LCA.

    Solution:
        Take the two pointers to the same depth. Then start traversing 
        up the parent till the two have the same node pointers, that is tha LCA.
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

// finds the depth of a node
int getDepth(Node<int>* root) {
    int depth = 0;

    while(root->parent) {
        ++depth;
        root = root->parent;
    }
    return depth;
}

// finds the LCA of two nodes
Node<int>* findLCA(unique_ptr<Node<int>>& root,
    unique_ptr<Node<int>>& node1, unique_ptr<Node<int>>& node2) {
    if (!root)
        return nullptr;

    auto iter1 = node1.get(), iter2 = node2.get();
    // first we find the depths of the two nodes
    int depth1 = getDepth(iter1);
    int depth2 = getDepth(iter2);

    // now take the nodes to same depth
    if (depth2 > depth1) {
        swap(iter1, iter2);
        swap(depth1, depth2);
    }
    while (depth1 != depth2) {
        iter1 = iter1->parent;
        --depth1;
    }
   
    // now that both the nodes are at same depth, we
    // move up till both the ptrs are same
    while (iter1 != iter2) {
        iter1 = iter1->parent;
        iter2 = iter2->parent;
    }
    return iter1;
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

    postOrderTraversal(root);
    cout << endl;
    cout << (findLCA(root, root->right->left, root->left->left))->data << endl;
    return 0;
}