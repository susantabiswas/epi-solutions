/*
    Problem:
        Given a linked list, reverse the nodes

    Input:
        head of the list

    Output:
        reversed list head
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

// reverses the nodes recursively
/* At each node we make the next node point to the current node */
Node* reverseListRecur(Node* head){
    // if this is the last node or NULL
    if(!head->next || !head){
        return head;
    }

    // next node
    Node* nextptr = head->next;
    // recurse further
    Node* rev_head = reverseListRecur(nextptr);
    // make the next node point to the current node
    nextptr->next = head;
    // make the current node point to NULL
    head->next = NULL;

    return rev_head;
}

int main(){
    Node* head1 = createNode(1);
    insertNode(head1, 3, 1);
    insertNode(head1, 8, 2);
    insertNode(head1, 12, 3);
    insertNode(head1, 13, 4);
    displayNodes(head1);

    Node* rev_head1 = reverseListIter(head1);
    displayNodes(rev_head1);

    head1 = createNode(1);
    insertNode(head1, 3, 1);
    insertNode(head1, 8, 2);
    insertNode(head1, 12, 3);
    insertNode(head1, 13, 4);
    displayNodes(head1);
    Node* rev_head2 = reverseListIter(head1);
    displayNodes(rev_head2);
    return 0;
}
