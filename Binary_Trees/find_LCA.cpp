/*
    Given two tree nodes, find the LCA.

    Solution:
        We start the traversal of tree, when we find any of the required
        nodes, we return the pointer to that node as the LCA, if later on
        again we find the other node then we return the pointer to it. If
        both the nodes are in the same subtree, then this will ensure that the 
        first appearing node wil be the ancestor.
        If we get pointers from both left and right subtree, then LCA will be
        the parent node, we return that as the LCA. 
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

// finds the LCA of two nodes
Node<int>* findLCA(unique_ptr<Node<int>>& root,
    unique_ptr<Node<int>>& node1, unique_ptr<Node<int>>& node2) {

    if (!root)
        return nullptr;

    // if the current node is one of the nodes
    if (root->data == node1->data || root->data == node2->data)
        return root.get();

    // search the left and right subtrees
    Node<int>* left = findLCA(root->left, node1, node2);
    Node<int>* right = findLCA(root->right, node1, node2);

    // if the two nodes are on different subtrees, then this is the 
    // first parent to have them on opposite sides, so it is the LCA
    if (left && right)
        return root.get();
    // return LCA if there
    if (left || right)
        return left ? left : right;

    // return null indicating that LCA is not found yet
    return nullptr;
}

// contains ancestor info
struct AncestorInfo {
    int nodes_found;    // tracks no. of required nodes found
    Node<int>* ancestor; // ptr to the LCA if there else null
};

// EPI solution
AncestorInfo searchLCA(unique_ptr<Node<int>>& root, unique_ptr<Node<int>>& node1,
                        unique_ptr<Node<int>>& node2) {
    if (!root)
        return { 0, nullptr };

    // check left and right subtree
    AncestorInfo left = searchLCA(root->left, node1, node2);
    if (left.ancestor)
        return left;
    AncestorInfo right = searchLCA(root->right, node1, node2);
    if (right.ancestor)
        return right;

    // if the current node is one of the required nodes,
    // then update nodes_found
    int nodes_found = left.nodes_found + right.nodes_found +
                    (root->data == node1->data || root->data == node2->data);
    
    // if both the nodes found then return current ptr else nullptr
    return {nodes_found, nodes_found == 2 ? root.get() : nullptr};
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
    cout << (findLCA(root, root->right->left, root->right->left->left))->data << endl;
    cout << (searchLCA(root, root->right->left, root->right->left->left)).ancestor->data;
    return 0;
}