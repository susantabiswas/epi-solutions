/*
	Given a binary tree. Print the nodes at same height, starting from top and left to right.
	Input: root of binary tree
	Output: 

	Solution:
		We can use a queue for doing BFS and keep track when a level is ending, then push the elements of that
		level to a vector.
		TC: O(n), n: no. of nodes
		SC: O(m), for queue, m: max nodes in any level 
		 
*/

#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

Node* createNode(const int& data) {
	try {
		Node* node = new Node;
		node->data = data;
		node->left = nullptr;
		node->right = nullptr;
		return node;
	
	} catch(bad_alloc& e) {
		cerr << e.what();
	}
}

// returns 2d vector which has nodes at same level
vector<list<int>> printNodesAtSameLevel(Node* root) {
	if(!root)
		return vector<list<int>>{};
		
	// for storing the nodes at same level
	vector<list<int>> tree_nodes;
	// for BFS
	queue<Node*> q;
	// for keeping track of nodes in current level
	int num_nodes = 0;
	Node* curr = nullptr;
	list<int> l;

	q.emplace(root);
	++num_nodes;
	
	while(!q.empty()) {
		curr = q.front();
		q.pop();
		l.emplace_back(curr->data);
		--num_nodes;

		// push the children nodes
		if(curr->left)
			q.emplace(curr->left);
		if(curr->right)
			q.emplace(curr->right);
		// when all the nodes of current level have been visited
		if(!num_nodes) {
			// move all the current level nodes
			tree_nodes.emplace_back(move(l));
			
			//set the no. of nodes for next level
			num_nodes = q.size();
		}
	}

	return tree_nodes;
} 

ostream& operator<< (ostream& out, vector<list<int>> arr) {
	for(const auto& v: arr) {
		for(const auto& el: v){
			cout << el << " ";
		}
		cout << endl;
	}
}

int main() {
	Node* root = createNode(1);
	
	root->left = createNode(2);
	root->right = createNode(3);
	
	root->left->left = createNode(4);
	root->left->right = createNode(5);
	
	root->right->left = createNode(6);
	root->right->right = createNode(7);
	
	root->right->right->right = createNode(8);
	
	cout << printNodesAtSameLevel(root);
	
	return 0;
}
 
