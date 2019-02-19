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
#include <queue>
using namespace std;

template<typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> left, right;
    Node<int>* right_sibling;
    
    Node(T data) : data(data), left(nullptr), right(nullptr),
                    right_sibling(nullptr) {}
};

// joins the right siblings using simple BFS
void joinRightSiblingsBFS(unique_ptr<Node<int>>& root) {
    queue<Node<int>*> q;
    q.emplace(root.get());
    
    // for keeping track of previous node
    Node<int>* prev = nullptr;
    Node<int>* curr = nullptr;
    // for keeping count of nodes in a level
    int level_count = q.size();

    while(!q.empty()) {
        // take the current node
        curr = q.front();
        q.pop();
        --level_count;

        // add the left and right childs
        if(curr->left)
            q.emplace(curr->left.get());
        if(curr->right)
            q.emplace(curr->right.get());

        // set the right sibling
        if(prev != nullptr) {
            prev->right_sibling = curr;
        }   

        // set the previous node
        prev = curr;
        
        // if this is the last node for current level
        if(level_count == 0) {
            // set the count for the next level
            level_count = q.size();
            prev = nullptr;
        }
    }

}

// joins right siblings in same level 
void joinRightSiblingsInSameLevel(Node<int>* parent) {
    while(parent) {
        // left child points to right child of parent
        parent->left->right_sibling = parent->right.get();
        // right child points to left child of next parent
        if(parent->right_sibling) {
            parent->right->right_sibling = parent->right_sibling->left.get();
        }
        // go to next parent node in previous level
        parent = parent->right_sibling;
    }
}

// joins the right siblings using epi method
void joinRightSiblings(unique_ptr<Node<int>>& root) {
    Node<int>* iter = root.get();
    // we start with root and do this till second last level
    while(iter && iter->left) {
        joinRightSiblingsInSameLevel(iter);
        // go to next level
        iter = iter->left.get();
    }
}

// for printing the right siblings
void printRightSiblings(unique_ptr<Node<int>>& root) {
	Node<int>* iter = root.get();
	while(iter) {
		// print the right siblings for current level
		Node<int>* level_iter = iter;
		while(level_iter) {
			if(level_iter->right_sibling)
				cout << level_iter->right_sibling->data <<" ";
			else
				cout << "NULL" << " ";
			level_iter = level_iter->right_sibling;
		}
		cout << endl;
		
		// go to next level
		iter = iter->left.get();
	}
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
               /  \   /	\
              4    5  6  7
                     
    */
    unique_ptr<Node<int>> root = make_unique<Node<int>>(1);
    root->left = make_unique<Node<int>>(2);
    root->right = make_unique<Node<int>>(3);
    root->left->left = make_unique<Node<int>>(4);
    root->left->right = make_unique<Node<int>>(5);

    root->right->left = make_unique<Node<int>>(6);
    root->right->right = make_unique<Node<int>>(7);
   
    inOrderTraversal(root);
    cout << endl;
	
	//joinRightSiblings(root);
	joinRightSiblingsBFS(root);
	printRightSiblings(root);
	
    return 0;
}
