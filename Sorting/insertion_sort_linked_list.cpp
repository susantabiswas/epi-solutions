/* 
	Sort a linked list.
	Here we do insertion sort, which takes O(n^2)

	Input: head of list
	Output: head of sorted list

	Solution:
		Insertion Sort:
      Start traversal of list, at any point if we get an element smaller than its previous
      we move it to a position in the list before it which is supposed to be sorted.
      Once we find the position in the list before it, we put it there and continue traversal
      from where we left.
      
		TC: O(n^2)
	*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node{
	int data;
	Node* next = NULL;
};

// for creating node
Node* createNode(const int& data) {
	try {
		Node* node = new Node;
		node->data = data;
		node->next = NULL;
		return node;
	} catch( bad_alloc e) {
		cerr << e.what();
	}
}

// for doing insertion sort of linked list
// TC: O(n^2)
Node* insertionSortLinkedList(Node* head) {
	if(!head || !head->next)
		return nullptr;

	Node* sorted_head = nullptr;
	Node* nextptr = nullptr;
	Node* prev = nullptr;
	Node* unsorted_data = nullptr;
	
	// current node being traversed
	Node* curr = head;
	
	// traverse the list till over
	while(curr && curr->next) {
		// if current data is greater than next, then fix it
		// by putting it at its correct position
		if(curr->data > curr->next->data) {
			sorted_head = head;
			// current data which is smaller than its previous data element 
			unsorted_data = curr->next;
			// next element of unsorted_data
			nextptr = curr->next->next;
			
			// since the list before current is supposed to be sorted,
			// we go back and look for first element which is greater than this
			// and put it there
			while(sorted_head->data < unsorted_data->data) {
				prev = sorted_head;
				sorted_head = sorted_head->next;
			}
			// place the unsorted_data just before the first bigger element
			prev->next = unsorted_data;
			unsorted_data->next = sorted_head;

			// make the original element before unsorted_data linked to the next element
			curr->next = nextptr;
		}
		else {
			curr = curr->next;
		}
	}
}

// shows the linked list
void showList(Node* head) {
	while(head) {
		cout << head->data <<" ";
		head = head->next;
	}
	cout << endl;
}

int main() {
	Node* head = createNode(1);
	head->next = createNode(2);
	head->next->next = createNode(6);
	head->next->next->next = createNode(51);
	head->next->next->next->next = createNode(2);	

	insertionSortLinkedList(head);
	showList(head);
	return 0;
}
