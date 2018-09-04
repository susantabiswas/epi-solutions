/*
    Problem:
        Given two sorted linked lists in ascending order, merge the two lists into one single sorted list inplace

    Input:
        head1: head of list 1
        head2: head of list 2

    Output:
        head: head of merged list

    TC: O(n+m), n and m:length of list1 and list2
*/

#include<iostream>
#include<vector>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

// create a node of Node type
Node *createNode(int data)
{
    Node *node = new Node;
    // when the node doesnt get any memory
    if (!node)
    {
        cout << "Error allocating memory!\n";
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

// for inserting node at a specified position
// TC: O(n), n = length of list
void insertNode(Node *&head, int data, int pos)
{
    // check if the list is empty or not
    if (!head)
    {
        // make a new node and make it the head
        head = createNode(data);
        return;
    }

    // if the node is to be inserted at the front
    if (pos == 0)
    {
        // create a node
        Node *node = createNode(data);
        // insert in front
        node->next = head;
        // make the current node as the current head
        head = node;
        //cout << "Node " << data << " added\n";
        return;
    }
    else
    {
        // for traversal
        Node *temp = head;
        int curr_pos = 0;
        // traverse till the node before the required position
        while (curr_pos < pos - 1 && temp)
        {
            // go to the next node
            ++curr_pos;
            temp = temp->next;
        }
        // check if position is possible or not
        // if the position is farther than the current length + 1,
        // then show error
        if (temp)
        {
            // create the node
            Node *node = createNode(data);
            // make the new node point to the previous node
            // that was at this position
            node->next = temp->next;
            // make the previous node point to the new node
            temp->next = node;
          //  cout << "Node " << data << " added\n";
        }
        else
        {
            cout << "Position is much farther than the length of the list\n";
        }
    }
}

// for displaying the nodes of the list
void displayNodes(Node *head)
{
    while (head)
    {
        cout << head->data << "-->";
        head = head->next;
    }
    cout << "NULL\n\n";
}


// merge two sorted linked lists
Node* mergeSortedLists(Node*& head1, Node*& head2){
    // head and rear for the new list
    Node* head = NULL, *rear = NULL;

    // check if any of the lists is empty or not
    if(!head1 || ! head2)
        return head1 ? head1 : head2;

    // link the first node of the list
    if(!head){
        if(head1->data < head2->data){
            head = head1;
            head1 = head1->next;
        }
        else{
            head = head2;
            head2 = head2->next;
        }
        // make the rear point to the first element and make its next NULL
        rear = head;
        rear->next = NULL;
    }

    // we will compare the nodes from the two lists and based on that
    // add that node to the merged list.
    while(head1 && head2){
        // when the node from 1st list is smaller or
        // equal to the 2nd list
        if(head1->data <= head2->data){
            // add the node to the end of merged list
            rear->next = head1;
            // traverse further in first list
            head1 = head1->next;
        }
        else{   // when the 2nd node has larger data
            rear->next = head2;
            head2 = head2->next;
        }
        // make the last element of the merge list point to NULL
        rear = rear->next;
        rear->next = NULL;
    }

    // add the remaining elements to the final list
    rear->next = head1 ? head1 : head2;

    return head;
}

int main(){
    Node* head1 = createNode(1);
    insertNode(head1, 3, 1);
    insertNode(head1, 8, 2);
    insertNode(head1, 12, 3);
    insertNode(head1, 13, 4);
    displayNodes(head1);

    Node *head2 = createNode(2);
    insertNode(head2, 3, 1);
    insertNode(head2, 4, 2);
    insertNode(head2, 9, 3);
    insertNode(head2, 16, 4);
    insertNode(head2, 19, 5);
    displayNodes(head2);

    Node* head = mergeSortedLists(head1, head2);
    displayNodes(head);
    return 0;
}
