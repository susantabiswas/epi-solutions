/*
    Implement a Linked List class
    
    TC: 
        Insertion: When the data is given only not pointer
                        head: O(1)
                        any position till last : O(n)
                    When pointer of node is given: O(1) 
        Deletion: When the data is given only not pointer
                        head: O(1)
                        any position till last : O(n)
                    When pointer of node is given: O(1)        
*/
#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class LinkedList {
    private:
    	template<typename t>
        struct Node {
            t data;
            shared_ptr<Node<t>> next;
            Node(t data) : data(data), next(nullptr) {};
        };    

        shared_ptr<Node<T>> head_ = nullptr;
        shared_ptr<Node<T>> tail_ = nullptr;
        
    public:
        // Adds a node to front of list
        void InsertFront(T data) {
            // if the list is empty
            if(head_ == nullptr) {
                head_ = make_shared<Node<T>>(Node<T>(data));
                tail_ = head_;
            }
            else {  
                // create a new node 
                shared_ptr<Node<T>> node = make_shared<Node<T>>(Node<T>(data));
                // make the next of new node point to what head is pointing
                node->next = head_;
                // make head point to the new list
                head_ = node;
            }
        }

        // Adds a node to back
        void InsertBack(T data) {
            // if the list is empty
            if(!head_) {
                InsertFront(data);
                return;
            }
			
            // add the node using the tail pointer
            shared_ptr<Node<int>> node = make_shared<Node<T>>(Node<T>(data));
        	tail_->next = node;
        	tail_ = node;
        }

        // Adds a node at position K
		bool InsertAtPosition(T data, int k) {
			// if the list is empty, insertion at K not possible
            if(Empty() || k <= 0)
                return false;
            
            // if insertion at head position
            if(k == 1) {
                InsertFront(data);
                return true;
            }
            // traverse list till K - 1th position
            auto iter = head_;
            int pos = 1;
            while(iter && pos < k - 1) {
                iter = iter->next;
                ++pos;
            }
            
            // if the list length is lesser than K, insertion not possible
            if(iter == nullptr) {
            	cout << "Position greater than list length!!\n";
            	return false;
            }
            	
            // create the new node
            shared_ptr<Node<T>> node = make_shared<Node<T>>(data);
            // make the new node point to list nodes after kth pos
            node->next = iter->next;
            // make the k-1th node point to new node
            iter->next = node;
            return true;
		}
		
        // Deletes a node at front
        bool DeleteFront() {
            // check if list is empty or not
            if(Empty())
                return false;
            
            auto temp = head_;
            head_ = head_->next;
        	// delete the node
            temp.reset();

            return true;
        }

        // Deletes a node from back
        bool DeleteBack() {
            // check if list is empty or not
            if(Empty())
                return false;
            // traverse till the second last node
            auto iter = head_;
            while(iter->next != tail_) {
                iter = iter->next;
            }
            
            // delete the last node
            tail_.reset();
            iter->next = nullptr;
            tail_ = iter;

            return true;
        }

        // Deletes a node from Kth position
        bool DeleteAtPosition(int k) {
            // check if list is empty or not
            if(Empty())
                return false;

            // if deletion at head position
            if(k == 1) {
                DeleteFront();
                return true;
            }

            // traverse list till K - 1th position
            auto iter = head_;
            int pos = 1;
            while(iter && pos < k - 1) {
                iter = iter->next;
                ++pos;
            }
            
            // if the list length is lesser than K, deletion not possible
            if(iter == nullptr) {
            	cout << "Position greater than list length!!\n";
            	return false;
            }
            
            auto temp = iter->next;
            iter->next = iter->next->next;
            // delete node
            temp.reset();
            return true;
        }

        // Checks if list is empty or not
		bool Empty() {
			return head_ == nullptr ? true : false;	
		}
		
        // Displays the linked list
        void Display() {
        	auto iter = head_.get();
        	while(iter) {
        		cout << iter->data << " ";
        		iter = iter->next.get();
        	}
        	cout << endl;
        }
};

int main() {
	LinkedList<int> l;
	l.InsertFront(1);
	l.InsertFront(2);
	l.InsertFront(3);
	
	l.InsertBack(1);
	l.InsertBack(2);
	
	l.Display();
	
	l.InsertAtPosition(22, 3);
	l.InsertAtPosition(33, 7);
	l.InsertAtPosition(44, 1);
	cout << l.InsertAtPosition(55, 99) << endl;
	
	l.Display();
	
	l.DeleteFront();
	l.Display();
    
    l.DeleteAtPosition(3);
	l.Display();
	
    l.DeleteAtPosition(1);
	l.Display();
	
	
    l.DeleteAtPosition(5);
	l.Display();
    
    l.DeleteBack();
	l.Display();
	
    
    return 0;
}    
