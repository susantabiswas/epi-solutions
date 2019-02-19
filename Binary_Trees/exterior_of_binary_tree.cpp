/*
    Given a binary tree, find the exterior nodes of binary tree. Exterior sequence :
    Nodes from root to leftmost leaf, then leftmost leaf to rightmost leaf and from there
    to tree root.

    Solution:
        We can simply do it by doing traversal thrice, each time focusing on one thing, but TC: O(h + n + h).
        To avoid revisiting nodes, we do the following:
        1. add root
        2. start traversal in left subtree and add the root to leaf nodes and the leaves in left subtree
        3. start traversal in righ subtree and add the leaf to root nodes and the leaves in right subtree
        
        TC: O(n)
        Sc: O(h), for recursive stack
*/
#include <iostream>
#include <list>
#include <memory>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;
    
    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

// adds the left boundary and leaves in left subtree
list< const unique_ptr<Node<int>>* > leftBoundaryAndLeaves(unique_ptr<Node<int>>& root,
                                                bool first_leaf_found) {
    list< const unique_ptr<Node<int>>* > l;

    if(root) {
        // node will only be added if it is a boundary or leaf node
        // if it is a leaf node add
        if(!root->left && !root->right) {
            l.emplace_back(&root);
            // after this we won't get any boundary nodes
            first_leaf_found = true;
        }
        // so we add nodes on path till the first leaf is encountered
        if(first_leaf_found == false)
            l.emplace_back(&root);
        
        l.splice(l.end(), leftBoundaryAndLeaves(root->left, first_leaf_found));
        l.splice(l.end(), leftBoundaryAndLeaves(root->right, first_leaf_found));
    }

    return l;
}

// adds the right subtree leaves and right boundary
// the right consists of node path in which every node is a right child or is a left child when
// its parent doesn't have a right child. Basically they are all the nodes on the first right subtree path 
list< const unique_ptr<Node<int>>* > rightLeavesAndBoundary(unique_ptr<Node<int>>& root,
															bool right_boundary) {
    list< const unique_ptr<Node<int>>* > l;

    if(root) {
		// here first we start with the leaves from left side, then once
		// we reach the last leaf we start adding the boundary nodes also
        
        // if the tree is going left, then it can only be right boundary if the current boundary node doesn't have a right child
        l.splice(l.end(), rightLeavesAndBoundary(root->left, right_boundary && root->right == nullptr));
        // right_boundary value for the path with all right childs will be true always
        l.splice(l.end(), rightLeavesAndBoundary(root->right, right_boundary));
    
    	// node will only be added if it is a boundary or leaf node
        // if it is a leaf node add
        if((!root->left && !root->right) || right_boundary) {
            l.emplace_back(&root);
        }
   }

    return l;
}

// finds the exterior view of binary tree
list< const unique_ptr<Node<int>>* > findBinaryTreeExterior(unique_ptr<Node<int>>& root) {
    list< const unique_ptr<Node<int>>* > exterior;
    // add the root first
    exterior.emplace_back(&root);
    // add the root-leftmost left path + leaves in left subtree
    exterior.splice(exterior.end(), leftBoundaryAndLeaves(root->left, false));
    // add leaves in right subtree + rightmost leaf to right subtree root path
    exterior.splice(exterior.end(), rightLeavesAndBoundary(root->right, true));

    return exterior;
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
    root->left = make_unique<Node<int>>(2);
    root->right = make_unique<Node<int>>(3);
    root->left->left = make_unique<Node<int>>(4);
    root->left->right = make_unique<Node<int>>(5);

    root->right->left = make_unique<Node<int>>(6);
    root->right->left->left = make_unique<Node<int>>(7);
   
    inOrderTraversal(root);
    cout << endl;
    auto head = findBinaryTreeExterior(root);
    
    cout << "Leaf Nodes:\n";
    for(const auto& a: head)
    	cout << a->get()->data << " ";
    cout << endl;
    return 0;
}
