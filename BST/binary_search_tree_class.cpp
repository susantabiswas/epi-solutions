/*
    Design a Binary Search Tree class.

    Solution:

        TC: Insertion: Avg: O(logn), worst: O(n) when skewed
            Deletion: Avg: O(logn), worst: O(n) when skewed
            Lookup: Avg: O(logn), worst: O(n) when skewed
        Sc: O(n), for recursive stack for each of the methods only, worst case: when skewed tree
*/
#include <iostream>
#include <list>
#include <memory>
#include <queue>
using namespace std;

template<typename T>
class BinarySearchTree{
    private:
    	template<typename t>
    	struct Node{
            t data;
            unique_ptr<Node<t>> left, right;

            Node(t data): data(data), left(nullptr), right(nullptr) {}
        };

        unique_ptr<Node<T>> root_ = nullptr;

    public:
        // for inserting a node
        bool Insert(T key) {
            /*
                We traverse the tree, every time comparing the key against the value of data 
                for each node, the target is to go the correct side of the tree, once the
                current node becomes NULL, we know we have reached the place and we create the node
                with key as the data value and link it to the parent node
            */
            
            // when the tree is empty
            if(root_ == nullptr) {
                root_ = make_unique<Node<T>>(Node<T>(key));
                return true;
            }
            else {
                Node<T>* curr = root_.get(), *parent = nullptr;
                // we will traverse till find a suitable position or find the key already inserted
                while(curr) {
                    parent = curr;
                    if(curr->data == key)       // when the key is already there
                        return false;
                    else if(curr->data < key)   // go right when current is smaller 
                        curr = curr->right.get();
                    else                        // go left when current is bigger
                        curr = curr->left.get();
                }

                // now we will just add the new node as a child
                if(key > parent->data)  
                    parent->right.reset(new Node<T>(key));
                else if(key < parent->data)
                    parent->left.reset(new Node<T>(key));
                return true;
            }
        }

        // for deleting a node
        bool Delete(T key) {
            /*
                For deletion we first find the key, if not found return false 
                else:
                    if the key is a leaf, delete and make its parent point to null
                    if the key has only one child, delete it and make its parent point
                        to that child instead
                    if the key has two children, then we take the successor(leftmost node of right subtree) 
                        for the current key value, then swap the successor with the key and delete the successor 
                        node from its position, as the successor will be leaf node.
                    return true
            */
            // deletion not possible with an empty tree
            if(!root_)
                return false;
            
            Node<T>* curr = getRoot(), *parent = nullptr;
            // start traversing till the node is found
            while(curr && curr->data != key) {
                parent = curr;
                curr = curr->data > key ? curr->left.get() : curr->right.get();
            }

            // when the key is not found
            if(curr == nullptr)
                return false;
            
            // now that the key is found, we will delete it
            // when the key is not a leaf node
            if(curr->right && curr->left) {
                // find the successor if right subtree exists
                Node<T>* successor = curr->right.get();
                Node<T>* successor_parent = nullptr;
                while(successor->left) {
                    successor_parent = successor;
                    successor = successor->left.get();
                }
                // update data value with successor
                curr->data = successor->data;
                // check if the successor is the leftmost node of right subtree
                if(!successor_parent) {		// if there is no left child of right subtree
                    curr->right.reset(successor->right.release());
                }
                else {	
                	// it is not necessary that the successor will be a leaf, it might have 
                	// a right subtree also
                    successor_parent->left.reset(successor->right.release());	
                }    
            }
            else if(curr->left) {   // when there is only left subtree 
                // return the left subtree of key as appropriate child of parent of key
                if(parent->left.get() == curr) {
                    // release returns the value of that pointer
                    parent->left.reset(curr->left.release());
                }
                else {
                    parent->right.reset(curr->left.release());
                }
            }
            else if(curr->right) { // when there is only right subtree
                // return the right subtree of key as appropriate child of parent of key
                if(parent->left.get() == curr) {
                    // release returns the value of that pointer
                    parent->left.reset(curr->right.release());
                }
                else {
                    parent->right.reset(curr->right.release());
                }
            }
            else {  // when key is a leaf node
                if(parent->left.get() == curr) {
                    // release returns the value of that pointer
                    parent->left.reset(nullptr);
                }
                else {
                    parent->right.reset(nullptr);
                }
            }

            return true;
        }
        
        // inorder traversal
		void inOrderTraversal(Node<T>* iter) {
		    if (iter) {
		        inOrderTraversal(iter->left.get());
		        cout << iter->data << " " ;
		    	inOrderTraversal(iter->right.get());
		     }
		}
		
		// for getting the root value
		Node<T>* getRoot() {
			return root_.get();
		}
};



int main() {
    BinarySearchTree<int> bst;
    bst.Insert(5);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(7);
    bst.Insert(3);
    bst.Insert(1);
    bst.inOrderTraversal(bst.getRoot());
    cout << endl;
    
    bst.Delete(5);
    bst.inOrderTraversal(bst.getRoot());
    return 0;
}
