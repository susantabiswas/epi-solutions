/*
    Given preorder traversal data, with null indicators for indicating null in traversal. Construct the tree.
    Solution:
        Since this is a binary tree with preorder traversal data given, it means that we are first going to the
        left subtree always then head to the right subtree. So we start traversing through the tree and each time 
        we try to link the left child of current node first, we continue till we get a null marker, if we
        get null, return and then go to right, then again do the same till we get null

        TC: O(n)
        Sc: O(h), for recursive stack
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <memory>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;
    
    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

unique_ptr<Node<int>> buildTreeFromPreorderTraversalHelper(vector<int>& preorder, 
                                                int* preorder_s, int preorder_e) {
    // go to next index
    ++(*preorder_s);
    
    // if traversal data has finised or null is encountered
    if(*preorder_s > preorder_e || preorder[*preorder_s] == NULL)
        return nullptr;
 
    // create node
    unique_ptr<Node<int>> root = make_unique<Node<int>>(Node<int>(preorder[*preorder_s]));
   
    // first deal with left subtree, then right subtree
    root->left = buildTreeFromPreorderTraversalHelper(preorder, preorder_s, preorder_e);
    root->right = buildTreeFromPreorderTraversalHelper(preorder, preorder_s, preorder_e);

    return root;
}

// builds binary tree from preorder traversal data
unique_ptr<Node<int>> buildTreeFromPreorderTraversal(vector<int>& preorder) {
    int preorder_s = -1;
    return buildTreeFromPreorderTraversalHelper(preorder, &preorder_s, preorder.size() - 1);
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
    vector<int> preorder = {1, 2, 4, NULL, NULL, 5, NULL, NULL,
    						3, 6, 7, NULL, NULL, NULL, NULL};

    unique_ptr<Node<int>> root = buildTreeFromPreorderTraversal(preorder);
	
    inOrderTraversal(root);
    cout << endl;
    return 0;
}
