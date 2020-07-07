/*
    Given a BST and three BST nodes, check if the tree nodes are ordered.
    The nodes are said to be ordered if either the first/third node is an ancestor of middle 
    node and the remaining node should be a descendent of middle.
    
    
    Solution:
        We can do normal search using the two nodes, trying one first and if it fails then trying the
        next one. The problem with this is if we start with the lower node first then it will traverse till the 
        first leaf, worst case:O(h).
        To prevent that, we start the search for the middle from both the nodes simultanously. We one of the
        nodes finds the other node, then not ordered, if it finds the middle, then we start searching from
        the middle for the other node. If the depth diff between the two nodes is 'd', then it will take O(d)
        if they are ordered, and in worst case it will take O(h)

        TC: O(d) for successful case, O(h): if nodes are not ordered 
        SC:  O(h)
*/
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <limits>
#include <utility>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;

    Node(T data): data(data), left(nullptr), right(nullptr) {}
};

// checks if three nodes of a BST are ordered or not
bool areNodesOrdered(unique_ptr<Node<int>>& root, unique_ptr<Node<int>>& node1,
                    unique_ptr<Node<int>>& node2, unique_ptr<Node<int>>& node3) {
    
    auto iter1 = node1.get();
    auto iter2 = node3.get();

    // start searching from both ends for node2, we stop when node2 is found or
    // either of the nodes bump into each other or they reach a leaf node
    while((iter1 && iter2) && (iter1 != node3.get() && iter2 != node1.get()) &&
        iter1 != node2.get() && iter2 != node2.get()) {
        iter1 = iter1->data > node2->data ? iter1->left.get() : iter1->right.get();
        iter2 = iter2->data > node2->data ? iter2->left.get() : iter2->right.get();
    }

    // if any of them has found node 2, then ancestor exists for sure otherwise not ordered for sure
    if(iter1 != node2.get() && iter2 != node2.get())
        return false;

    // one of the nodes is an ancestor of node2, so we search for the other node from node2
    auto descendent = iter1 == node2.get() ? node3.get() : node1.get();

    // now we search for descendent
    auto iter = node2.get();
    while(iter && iter != descendent) {
        iter = iter->data > descendent->data ? iter->left.get() : iter->right.get();
    }

    // if the middle node has reached a leaf node then they are not ordered
    return iter == nullptr ? false : true;
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
    
    // 2, 7, 6
    cout << endl << areNodesOrdered(root,  root->left, root->right->left, root->right->left->left);
    return 0;
}    
