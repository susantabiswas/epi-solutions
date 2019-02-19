/*
    Given a binary tree, create a linked list from the leaves of the tree, from left to right order.
    Solution:
        Start traversal in either inorder or preorder, then once leaf is reached, add to list.
        We create a list for each penultimate level subtree and then append it to the previous call list.

        TC: O(n)
        Sc: O(h), for recursive stack + hash table
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

// creates a linked list from leaf nodes of a binary tree
list< const unique_ptr<Node<int>>* > createListFromLeaves(unique_ptr<Node<int>>& root) {
   // we create a list for each penultimate level subtree and then append it to the previous call list
    list< const unique_ptr<Node<int>>* > leaf_list;
    
    if(!root)
    	return leaf_list;
    	
    // if current is a leaf node, add to list
    if(!root->left && !root->right) {
        leaf_list.emplace_back(&root);
    }

    // add the leaves from left subtree first, then add from right subtree
    leaf_list.splice(leaf_list.end(), createListFromLeaves(root->left));
    leaf_list.splice(leaf_list.end(), createListFromLeaves(root->right));
    return leaf_list;
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
    auto head = createListFromLeaves(root);
    
    cout << "Leaf Nodes:\n";
    for(const auto& a: head)
    	cout << a->get()->data << " ";
    cout << endl;
    return 0;
}
