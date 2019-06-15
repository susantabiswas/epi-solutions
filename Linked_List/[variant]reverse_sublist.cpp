/*
    Problem:
        Given a linked list and range 'a' and 'b'. Reverse the nodes in the range [a,b]

    Input:
        head of the list
        a: int
        b: int

    Output:
        head of the transformed list
    TC: O(n)
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

// reverses the sublist in a linked list
Node* reverseSublist(Node*& head, int a, int b){
    // if the list is NULL
    if(!head)
        return NULL;

    // we traverse the list and find the ath and bth node
    // then we reverse the list from a to b and connect it with
    // the remaining list

    // for keeping track of position
    int count = 1;
    Node* start_prev = NULL;    // stores the node before the start node
    // addr of first  and last element of the sublist
    Node* ath_node = NULL, *bth_node = NULL;
    // new head
    Node* new_head = head;

    // traverse the list till the bth node
    while(head){
        // when the next node is the starting node
        if(count == a-1 && count != 1){
            start_prev = head;
        }
        else if(count == a)
            // addr of ath_node element of the sublist
            ath_node = head;

        // when the node is the bth node
        else if(count == b){
            bth_node = head;
            // go to the node bth node is pointing,
            // the last element of the reversed list will point to this
            head = head->next;
            // make the bth node point to NULL
            bth_node->next = NULL;
            break;
        }
        ++count;
        head = head->next;
    }

    // when the ath node is not the head element of the given list
    if(start_prev){
        // reverse the sublist
        start_prev->next = reverseListIter(ath_node);
    }
    else{   // when the ath node is the head node in the given list
        new_head = reverseListIter(ath_node);
    }
    // join the last node of sublist
    ath_node->next = head;

    return new_head;
}

int main(){
    Node* head1 = createNode(10);
    for(int i = 9; i >= 0; i--)
        insertNode(head1, i, 0);
    displayNodes(head1);

    Node* new_head = reverseSublist(head1, 3, 10);
    displayNodes(new_head);
    return 0;
}
