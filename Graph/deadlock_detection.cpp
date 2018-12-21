/*
	Given a graph, find whether exists a cycle or not.
	
	Input: Directed graph
	Output: bool
	
	Solution: 
		We can use DFS for this. We associate three states using 3 colors: white,
		grey and black.
		White: initial state
		Grey: Visited once and being processed
		Black: Processed once
		
		We start with white color, then for each node being visited for the first
		time we make it grey and recurse further. Once the call returns back to a 
		node, we make the color for that node as black, indicating that has finished 
		processing. While doing DFS we encounter a node which is of grey color, then that means 
		we have a loop in there.
		
	TC: O(V + E)
	SC: O(V)
*/

#include <iostream>
#include <vector>
using namespace std;

struct Vertex{
	// states with default state white
	enum Color { white, grey, black} color = white;
	int data;
	vector<Vertex*> edges;
};

// for creating a vertex node
Vertex* createNode(const int& data){
	return new Vertex{Vertex :: white, data, vector<Vertex*>{}};	
}

// creates a graph with given no. of vertices
// gives the serial data values to the nodes and sets edges empty
vector<Vertex*> createGraph(const int& n){
	vector<Vertex*> g; 
	
	for(int i = 0; i < n; i++){
		g.emplace_back(createNode(i));
	}
	
	return g;
}

// for adding an edge from 'u' to 'v'
void addEdge(Vertex* & u, Vertex* & v){
	u->edges.push_back(v);		
}

// for printing the edges of the graph
void printGraph(const vector<Vertex*>& g){
	cout << "GRAPH:\n";
	for(const Vertex* u: g){
		cout << u->data << ": ";
		for(const Vertex* v: u->edges){
			cout << v->data << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// using DFS we check if any node reaches back to its previous parent node or not
bool isCyclePresent(Vertex* curr, Vertex* prev){
	// check if the color is grey or not, if it is then that means
	// that the current node is already there in the recursion stack
	// and because of the cycle again that node has been reached
	if(curr->color == Vertex::grey)
		return true;
		
	// else if it is the first time, make it grey
	curr->color = Vertex::grey;
	
	// do DFS for its adjacent nodes
	for(const auto next: curr->edges){
		if(next != prev && next->color != Vertex::black && isCyclePresent(next, curr))
			return true;
	}
	
	// now that the processing has been done, change the state to black 
	curr->color = Vertex::black;
	return false;
	
}

// checks if deadlock is present or not. Basically we check for existence of a cycle.
bool isDeadlockPresent(vector<Vertex*>& g){
	for(Vertex* curr: g){
		if(curr->color == Vertex::white && isCyclePresent(curr, nullptr))
			return true;
	}	
	return false;	
}

int main() {
	// create graph
	vector<Vertex*> g = createGraph(5);
	// add edges
	addEdge(g[0], g[1]);
	addEdge(g[1], g[2]);
	addEdge(g[2], g[0]);
	addEdge(g[2], g[3]);
	addEdge(g[3], g[4]);
	printGraph(g);
	
	cout << "Deadlock present: " << isDeadlockPresent(g);
	return 0;
}
