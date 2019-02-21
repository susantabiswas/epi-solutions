/*
    Given a sorted array, construct a BST of minimum height.
    Solution:
        Tree will be of minimum height when the subtrees have comparable number of nodes.
        So each time we can select the middle element of array as the root and recurse on the left and right 
        subarrays for left and right subtrees respectively.

        TC: T(n) = 2T(n/2) + O(1) ~ O(n) 
        Sc: O(n), for n sized array
*/
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;

    Node(T data): data(data), left(nullptr), right(nullptr) {}
};

unique_ptr<Node<int>> constructBstFromArrayHelper(vector<int>& arr, int l, int h) {
    if(l > h)
        return nullptr;

    // select the middle element as the root
    int middle_idx = l + (h - l) / 2;
    // create the node
    unique_ptr<Node<int>> root = make_unique<Node<int>>(Node<int>(arr[middle_idx]));
    // left subtree
    root->left = constructBstFromArrayHelper(arr, l, middle_idx - 1);
    // right subtree
    root->right = constructBstFromArrayHelper(arr, middle_idx + 1, h);

    return root;
}

// constructs a BST of min height 
unique_ptr<Node<int>> constructBstFromArray(vector<int>& arr) {
    return constructBstFromArrayHelper(arr, 0, arr.size() - 1);
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
                2      6
               /  \     \
              1    3     7
                		  \
                		   8
    */
    vector<int> arr = {1, 2, 3, 5, 6, 7, 8};
    unique_ptr<Node<int>> root = constructBstFromArray(arr);
    inOrderTraversal(root.get());
   
    return 0;
}
