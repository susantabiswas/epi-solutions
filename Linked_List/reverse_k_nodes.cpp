/*
    Problem:
        Given a positive integer 'k' and a linked list, reverse 'k' nodes
        at a time.
        eg: 1,2,3,4,5,6,7,8,9 and k = 3
            3,2,1,6,5,4,9,8,7

    Input:
        k: intger
        head of the linked list

    Output:
        head of linked list after reversal
*/

#include<iostream>
#include<vector>
using namespace std;

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
        //cout << "Node " << data <<" added\n";
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
            //cout << "Node " << data << " added\n";
        }
        else{
            cout << "Position is much farther than the length of the list\n";
        }
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

// reverses the list iteratively
// TC: O(n)
Node* reverseListIter(Node* head){
    // when the list is empty
    if(!head)
        return head;

    // pointer to the previous node
    Node* prev = NULL;
    Node* next_node = NULL;

    // traverse the list
    while(head->next){
        // next node addr
        next_node = head->next;
        // reverse the current node
        head->next = prev;
        // store the addr of current node
        prev = head;
        head = next_node;
    }
    // link the last node
    head->next = prev;
    return head;
}

// reverse the list with k nodes at a time
Node* reverseKNodes(Node* head, int k){
    if(!head)
        return NULL;

    // starting and ending nodes of sublist
    Node* start = head, *last = NULL;
    int count = 1;
    // traverse the first k nodes
    while(count++ < k){
        head = head->next;
    }
    // make the last node point to NULL
    last = head;
    head = head->next;
    last->next = NULL;
    // reverse the first k nodes
    Node* new_head = reverseListIter(start);
    
    while(head){
        
    }
}

int main(){
    
    return 0;
}