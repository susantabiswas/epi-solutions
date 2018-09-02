/*
    Problem:
        Make a linked list and write functions for inserting and deleting element
        nodes at any position

    Input:
        head: head of list
        pos: position to perform operation, it is zero indexed

    Output:
       updated list
*/

#include<iostream>
#include<vector>
using namespace std;//deletion at any position
void delPos(Node** head,int pos){
	//check for underflow
	if(*head == NULL){
		cout <<"Underflow!";
		return;
	}

	//check if deletion is to occur at 1st position or not
	if(pos==1){
		Node* t = *head;
		*head = (*head)->next;
		delete t;
	}
	else{
		int count = 1;
		Node* t = *head;
		while(t->next && count<pos-1){
			++count;
			t=t->next;
		}

		//check for out of bound
		if(count < pos-1 || t->next == NULL){
			cout<<"Posiiton out of bound";
			return;
		}

		Node* t1 = t->next;
		t->next = t->next->next;
		delete t1;
	}
}

//deletion at end
void delEnd(Node** head){
	Node* t = *head;
	Node* prev = NULL;
	while(t->next){
		prev = t;
		t = t->next;
	}
	prev->next = NULL;
	delete t;
}

struct Node{
    int data;
    Node* next;
};

// create a node of Node type
Node* createNode(int data){
    Node* node = new Node;
    // when the node doesnt get any memory
    if(!node){
        cout << "Error allocating memory!\n";
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

// for inserting node at a specified position
// TC: O(n), n = length of list
void insertNode(Node*& head, int data, int pos){
    // check if the list is empty or not
    if(!head){
        // make a new node and make it the head
        head = createNode(data);
        return;
    }

    // if the node is to be inserted at the front
    if(pos == 0){
        // create a node
        Node* node = createNode(data);
        // insert in front
        node->next = head;
        // make the current node as the current head
        head = node;
        cout << "Node " << data <<" added\n";
        return;
    }
    else{
        // for traversal
        Node* temp = head;
        int curr_pos = 0;
        // traverse till the node before the required position
        while(curr_pos < pos - 1 && temp){
            // go to the next node
            ++curr_pos;
            temp = temp->next;
        }
        // check if position is possible or not
        // if the position is farther than the current length + 1,
        // then show error
        if(temp){
            // create the node
            Node* node = createNode(data);
            // make the new node point to the previous node
            // that was at this position
            node->next = temp->next;
            // make the previous node point to the new node
            temp->next  = node;
            cout << "Node " << data << " added\n";
        }
        else{
            cout << "Position is much farther than the length of the list\n";
        }
    }

}


// for deleting a node at a given position
// TC: O(n), n: length of list
void deleteNode(Node*& head, int pos){
    // check if the list is empty or not
    if(!head){
        cout << "Empty list!\n";
        return;
    }

    // when the list is not empty
    // traverse till the node before the required position

    if(pos == 0){
        Node* del_node = head;
        head = head->next;
        delete del_node;
        cout << "Node deleted\n";
        return;
    }
    // for traversal
    Node* temp = head;
    int curr_pos = 0;

    // traverse till the node before the target node
    while(temp->next && curr_pos < pos - 1){
        ++curr_pos;
        temp = temp->next;
    }

    // check if the last node has been reached or not
    if(!temp->next || curr_pos < pos - 1){
        cout << "Given position out of bound\n";
        return;
    }
    else{
        // make the previous node point to the what the node
        // at that position was pointing at
        Node* del_node = temp->next;
        temp->next = temp->next->next;
        delete del_node;
        cout << "Node deleted\n";
    }
}

// for displaying the nodes of the list
void displayNodes(Node* head){
    while(head){
        cout << head->data << "-->";
        head = head->next;
    }
    cout << "NULL\n\n";
}


int main(){
    // create the list
    Node* head = NULL;

    // insert nodes
    for(int i = 0; i< 5; i++)
        insertNode(head, i, 0);
    displayNodes(head);

    // out of bound position
    insertNode(head, 99, 55);
    // in between pos
    insertNode(head, 88, 3);
    displayNodes(head);

    // last position
    insertNode(head, 77, 6);
    insertNode(head, 66, 7);
    displayNodes(head);

    // first position
    insertNode(head, 55, 0);
    // display the list
    displayNodes(head);


    //deletion
    //begining
    deleteNode(head, 0);
    displayNodes(head);
    //end
    deleteNode(head, 8);
    displayNodes(head);
    //in between
    deleteNode(head, 4);
    displayNodes(head);

    deleteNode(head, 99);
    return 0;
}
