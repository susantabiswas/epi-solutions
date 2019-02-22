/*
    Given a BST and an interval range [a, b]. Find all the nodes which lie in this range.
    
    Solution:
        Since this is a BST, we can do prunning while searching for the nodes lying in this range interval.
        If any node is greater than the lower bound, then its left subtree cannot have any node which belong to that
        interval. Similarly if the node is greater than the upper bound, then its right subtree cannot have any node
        which belong to that interval. If the node lie in that range then we search its left and right subtrees from there.

        TC: O(h + m), m: nodes lying in that range
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

void findIntervalNodesHelper(unique_ptr<Node<int>>& root, pair<int, int>& interval,
                            vector<Node<int>*>& result) {
    if(!root)
        return;
    // if current node lie in the interval
    if(root->data >= interval.first && root->data <= interval.second) {
        result.emplace_back(root.get());
        findIntervalNodesHelper(root->left, interval, result);
        findIntervalNodesHelper(root->right, interval, result);
    }
    else if(root->data < interval.first) 
        findIntervalNodesHelper(root->right, interval, result);
    else
        findIntervalNodesHelper(root->left, interval, result);
}

// finds all the BST nodes that lie in the given interval.
vector<Node<int>*> findIntervalNodes(unique_ptr<Node<int>>& root,
                                    pair<int, int> interval) {
    vector<Node<int>*> result;
    findIntervalNodesHelper(root, interval, result);
    return result;
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
    
    pair<int, int> interval = make_pair<int, int>(2, 4);
    vector<Node<int>*> result = findIntervalNodes(root, interval);
    
    cout << endl;
    for(const auto& a: result)
    	cout << a->data << " ";
    return 0;
}    
