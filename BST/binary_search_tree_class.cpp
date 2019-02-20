/*
    Given a perfect binary tree with extra right_sibling field, which should points to the right node in that
    level. Initially this extra field is empty for all the nodes, make the extra field point to the correct locations.

    Solution:
        Can be done in two ways:
        1. Simple BFS, in which for each level we check if there is any node behind or not, if it is there we make its
            right_sibling point to that.
        2. Since this is a perfect binary tree, there won't be any case of missing children, so for a left child its next_sibling 
            will be the right child of its parent and for the right child the right_sibling will point to the left child of the 
            right_sibling of its parent if exists else null.

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

// joins the right siblings using simple BFS
void joinRightSiblingsBFS() {

}

// joins right siblings in same level 
void joinRightSiblingsInSameLevel() {

}

// joins the right siblings using epi method
void joinRightSiblings(unique_ptr<Node<int>>& root) {
    auto iter = root;
    // we start with root and do this till second last level
    while(iter && iter->left) {
        joinRightSiblingsInSameLevel(iter);
        // go to next level
        iter = iter->left;
    }
}

// finds the exterior view of binary tree
list<const unique_ptr<Node<int>>*> findBinaryTreeExterior(unique_ptr<Node<int>>& root) {
    list<unique_ptr<Node<int>>*> exterior;
    // add the root first
    exterior.emplace_back(&root);
    // add the root-leftmost left path + leaves in left subtree
    exterior.splice(exterior.end(), leftBoundaryAndLeaves(root->left, false));
    // add leaves in right subtree + rightmost leaf to right subtree root path
    //exterior.splice(exterior.end(), rightLeavesAndBoundary(root->right));

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