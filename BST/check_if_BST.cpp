/*
    Given a binary tree, check if it is a BST.
    
    Solution:
        There are multiple ways of doing this:
        1.  Do inorder traversal of the tree, check if each element is greater than its previous
            element or not. Inorder traversal of a BST is a sorted array.

        2.  For each root, there is a range of values for its left and right subtree elements. For the right
            subtree, the min value should be atleast 1 more than the root. For left subtree the max value is
            atmost 1 less than the root. So each time we go down, we pass the updated range, if any element 
            doesn't fall in the range, then not BST
        
        3.  We use the range technique but with BFS, since in above we were doing DFS, so if the conflicting node is 
            in upper level but towards right, then a lot of traversal needs to be done. So we do BFS, everytime with the current
            node we save the range limit for its child nodes, so when we are popping the nodes for adding the
            child nodes, at that time we check if it is in range or not, then for the child nodes we
            update the limits and push alongside them.

        TC: O(n)
        SC: DFS: O(logn), for n sized array
	    BFS: O(2^n + 1), last level with leaf nodes
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

bool checkBstUsingDfsHelper(Node<int>* root, int lower_limit,
                                         int upper_limit) {
    if(!root)
        return true;
    
    // check current data value
    if(root->data < lower_limit || root->data > upper_limit)
        return false;

    return checkBstUsingDfsHelper(root->left.get(), lower_limit, root->data - 1) && 
           checkBstUsingDfsHelper(root->right.get(), root->data + 1, upper_limit);
}

// checks if a binary tree is a BST using DFS
bool checkBstUsingDfs(unique_ptr<Node<int>>& root) {
	return checkBstUsingDfsHelper(root.get(), numeric_limits<int>::min(), 
					numeric_limits<int>::max());
}


struct BFSElement {
    Node<int>* node;
    int lower_limit;
    int upper_limit;
};

// checks if a binary tree is a BST using BFS
bool checkBstUsingBfs(unique_ptr<Node<int>>& root) {
    queue<BFSElement> q;
    // initial root with [-INF, INF] range
    q.emplace(BFSElement{root.get(), numeric_limits<int>::min(), 
                		   numeric_limits<int>::max() }
             );
    
    BFSElement curr;

    while(!q.empty()) {
        curr = q.front();
        q.pop();

        // check if current is not within range or not
        if(curr.node->data > curr.upper_limit || 
            curr.node->data < curr.lower_limit)
            return false;

        // add the child nodes
        if(curr.node->left)
            q.emplace(BFSElement{curr.node->left.get(), curr.lower_limit, curr.node->data - 1});
        if(curr.node->right)
            q.emplace(BFSElement{curr.node->right.get(), curr.node->data + 1, curr.upper_limit});
    }
    return true;
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
    cout << endl << checkBstUsingBfs(root);
    cout << endl << checkBstUsingDfs(root);
    return 0;
}
