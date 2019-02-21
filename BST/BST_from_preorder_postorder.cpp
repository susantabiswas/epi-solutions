/*
    Given a preorder or postorder traversal sequence, construct BST from it. It is known that the sequence is
    of a BST.
    
    Solution:
        We build the tree in incremental fashion.
        We keep a index which tracks the current element of the traversal. 
        For preorder:
            Each node is a root node. So we start building the tree with the first element as root.
            We preorder first the left subtree is formed then the right subtree is formed. So with each
            node for the recursion call we send the range in which its child can exists, if the next
            element is in that range, we add it as its child, otherwise make the child NULL, then we go up and 
            continue recursion in similar manner.

        For postorder:
            The conecept is same, just that the upper root is always visited last, so if we start from back of the
            sequence we will have the root of the tree and here first the right subtree is created then left subtree.
             
        TC: O(n)
        SC: O(n) for n elements
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

unique_ptr<Node<int>> buildBSTFromPreorderHelper(vector<int>& preorder, int& curr_idx, 
                                        int lower_limit, int upper_limit) {
    // if the sequence has finished
    if(curr_idx >= preorder.size())
        return nullptr;

    int key = preorder[curr_idx];
    
    // if the current node doesn't lie in the range
    if(key < lower_limit || key > upper_limit) {
        return nullptr;
    }

    // current node lie in the range, so it can be a created
    unique_ptr<Node<int>> root = make_unique<Node<int>>(Node<int>(key));
    // go to next root element
    ++curr_idx;

    // construct its left and right subtrees
    root->left = buildBSTFromPreorderHelper(preorder, curr_idx, lower_limit, key - 1);
    root->right = buildBSTFromPreorderHelper(preorder, curr_idx, key + 1, upper_limit);
    
    return root;
}

// creates BST from preorder traversal sequence
unique_ptr<Node<int>> buildBSTFromPreorder(vector<int>& preorder) {
    int curr_idx = 0;
    return buildBSTFromPreorderHelper(preorder, curr_idx,
                 numeric_limits<int>::min(), numeric_limits<int>::max());
}

unique_ptr<Node<int>> buildBSTFromPostorderHelper(vector<int>& postorder, int& curr_idx, 
                                        int lower_limit, int upper_limit) {
    // if the sequence has finished
    if(curr_idx < 0)
        return nullptr;

    int key = postorder[curr_idx];
    
    // if the current node doesn't lie in the range
    if(key < lower_limit || key > upper_limit) {
        return nullptr;
    }

    // current node lie in the range, so it can be a created
    unique_ptr<Node<int>> root = make_unique<Node<int>>(Node<int>(key));
    // go to next root element
    --curr_idx;

    // construct its right and left subtrees
    root->right = buildBSTFromPostorderHelper(postorder, curr_idx, key + 1, upper_limit);
    root->left = buildBSTFromPostorderHelper(postorder, curr_idx, lower_limit, key - 1);
    
    return root;
}

// creates BST from postorder traversal sequence
unique_ptr<Node<int>> buildBSTFromPostorder(vector<int>& postorder) {
    int curr_idx = postorder.size() - 1;
    return buildBSTFromPostorderHelper(postorder, curr_idx,
                 numeric_limits<int>::min(), numeric_limits<int>::max());
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
    vector<int> preorder = {5, 2, 1, 3, 8, 7, 6, 9};
    vector<int> postorder = {1, 3, 2, 6, 7, 9, 8, 5};
    unique_ptr<Node<int>> root_from_preorder = buildBSTFromPreorder(preorder);
    
    inOrderTraversal(root_from_preorder.get());
    
    unique_ptr<Node<int>> root_from_postorder = buildBSTFromPostorder(postorder);
    cout << endl;
    inOrderTraversal(root_from_postorder.get());
    return 0;
}    
