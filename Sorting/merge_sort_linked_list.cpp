/* 
	Sort a linked list.
	Here we do merge sort, which takes O(nlogn) and since it is not array so no extra space except for
	recursion stack.
	Input: head of list
	Output: head of sorted list
	Solution:
		
		Merge Sort:
			Split the list in half. Do this recursively till the list has only one node.
			After recursion of left and right sides, merge them.	

			TC: O(nlogn)
			SC: O(1)
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


// shows the linked list
void showList(Node* head) {
	while(head) {
		cout << head->data <<" ";
		head = head->next;
	}
	cout << endl;
}

// for merging two linked lists in sorted order
Node* mergeLinkedLists(Node* head1, Node* head2) {
	// return the other list if either is null
	if(!head1 || !head2)
		return head1 ? head1 : head2;

	// head pointer for merged sorted list
	Node* sorted_head = nullptr;
	// for traversing the sorted list
	Node* sorted_list = nullptr;
	
	while(head1 && head2) {
		// when this is the first node of merged list
		if(!sorted_head) {
			if(head1->data <= head2->data) {
				sorted_head = head1;
				head1 = head1->next;
			} else {
				sorted_head = head2;
				head2 = head2->next;
			}
			sorted_head->next = nullptr;
			sorted_list = sorted_head;
		}
		// when the sorted_head is not null
		else {	
			if(head1->data <= head2->data) {
				sorted_list->next = head1;
				head1 = head1->next;
			} else {
				sorted_list->next = head2;
				head2 = head2->next;
			}
			
			// advance to the last added node
			sorted_list = sorted_list->next;
		}
		
		// make the last added node of sorted list point to null
		sorted_list->next = nullptr;
	}
	
	// add the remaining elements of list 1 if it exists
	if(head1) {
		sorted_list->next = head1;
	}

	// add the remaining elements of list 2 if it exists
	if(head2) {
		sorted_list->next = head2;
	}

	return sorted_head;
}

// for finding the middle node of list
Node* findMiddleNode(Node* head) {
	// when empty or with just 1 node
	if(!head || !head->next)
		return head;

	// we use two pointers:
	// slow: moves one step at a time
	// fast: moves two steps at a time
	// by the time fast completes the traversal, slow will be at next of middle
	Node* slow = head, *fast = head, *prev = nullptr;
	
	// do the traversal
	while(fast && fast->next) {
		fast = fast->next->next;
		prev = slow;
		slow = slow->next;
	}

	return prev;
}

// for doing merge sort
Node* mergeSortLinkedList(Node* head) {
	// if the list has only one node or empty
	if(!head || !head->next)
		return head;
		
	// find the middle node of list
	Node* middle = findMiddleNode(head);
	
	// split the list in two parts and recurse and merge them
	Node* list_starting_middle = middle->next;
	middle->next = nullptr;

	Node* sorted_left = mergeSortLinkedList(head);
	Node* sorted_right = mergeSortLinkedList(list_starting_middle);
	
	Node* sorted_head = mergeLinkedLists(sorted_left, sorted_right);

	return sorted_head;
}



int main() {
	Node* head = createNode(1909);
	head->next = createNode(2222);
	head->next->next = createNode(6);
	head->next->next->next = createNode(51);
	head->next->next->next->next = createNode(254);	

	Node* sorted_head = mergeSortLinkedList(head);
	showList(sorted_head);

	return 0;
}
