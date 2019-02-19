/*
    Given traversal orders in inorder and preorder. Contruct a binary tree from this traversal data.

    Solution:
        Preorder always gives the root of a tree first and inorder first traverse the left, current root and
        right subtree. So the first element of preorder is the root of the tree, we find the root in inorder,
        then the nodes on its left form the left subtree and nodes on its right form the right subtree.
        
        For a skewed tree, the root will be at some extreme pos., so each time we do root lookup, we 
        are doing 1 + 2 + 3 ....+ n-1 ~ O(n^2) for a left skewed tree. To make this better
        we can use a hash table, mapping each the node data entry to their inorder traversal index.
        
        TC: O(n)
        Sc: O(h + n), for recursive stack + hash table
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

unique_ptr<Node<int>> buildTreeFromTraversalHelper(vector<int>& inorder, int inorder_s, int inorder_e,
                                        vector<int>& preorder, int preorder_s, int preorder_e,
                                        unordered_map<int, int>& inorder_mapping) {
    // when there is no node
    if(preorder_s > preorder_e || inorder_s > inorder_e)
        return nullptr;

    // current node data
    int root_data = preorder[preorder_s];
    // index of current node in order traversal 
    int root_idx = inorder_mapping[root_data];
    // number of nodes in left subtree
    int num_nodes_left = root_idx - inorder_s;
    
    // create current node
    unique_ptr<Node<int>> root = make_unique<Node<int>>(Node<int>(root_data));
    root->left = buildTreeFromTraversalHelper(inorder, inorder_s, root_idx - 1, 
                                              preorder, preorder_s + 1, preorder_s + num_nodes_left,
                                              inorder_mapping);
                                              
    root->right = buildTreeFromTraversalHelper(inorder, root_idx + 1, inorder_e,
                                               preorder,  preorder_s + num_nodes_left + 1, preorder_e,
                                               inorder_mapping);

    return root;
}

// builds binary tree from inorder and preorder traversal data
unique_ptr<Node<int>> buildTreeFromTraversal(vector<int>& inorder, vector<int>& preorder) {
    // make a mapping for inorder indices
    unordered_map<int, int> inorder_mapping;
    for(int i = 0; i < inorder.size(); i++) {
        inorder_mapping[inorder[i]] = i;
    }

    return buildTreeFromTraversalHelper(inorder, 0, inorder.size() - 1, 
                                    preorder, 0, preorder.size() - 1,
                                    inorder_mapping);
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
    vector<int> inorder = {4, 2, 5, 1, 7, 6, 3};
    vector<int> preorder = {1, 2, 4, 5, 3, 6, 7};

    unique_ptr<Node<int>> root = buildTreeFromTraversal(inorder, preorder);
	
    inOrderTraversal(root);
    cout << endl;
    return 0;
}
