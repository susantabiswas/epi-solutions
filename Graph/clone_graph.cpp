/*
	Given a vertex of a directed graph, the task is to clone the graph that is reachable from that
	vertex. The clone should be a copy.
	
	Input: vertex (Structure: int lablel, list of edges)
	Output: Graph Clone, return the clone vertex of the input vertex
	
	Solution:
		We use graph traversal for reaching the vertices. We use hash table for keeping track of
		unvisited nodes. During traversal for every new edge we make a corresponding clone.
		
		TC: O(V + E)
		SC: O(V + E): for creating the graph and for hash table
*/
#include<iostream>
#include<unordered_map>
#include<deque>
#include<vector>
using namespace std;

// strcuture for vertex
struct Vertex{
	int data;
	deque<Vertex*> edges;
};

// for creating a graph vertex
Vertex* createNode(const int& data){
	Vertex* vertex = new Vertex;
	if(vertex){
		vertex->data = data;
		vertex->edges = deque<Vertex*>{};
	}
	return vertex;
}

// for creating a graph with input number of vertices 
vector<Vertex*> createGraph(const int& count){
	// vector of all graph nodes
	vector<Vertex*> g;
	
	for(int i = 0; i < count; i++){
		g.emplace_back(createNode(i));	
	}
	
	return g;
}

// for adding an edge to the graph
void addEdge(Vertex*& u, Vertex*& v){
	u->edges.push_back(v);	
}

// for printing the graph
void printGraph(const vector<Vertex*>& g){
	for(auto node: g){
		cout << node->data << ": ";
		for(auto edge: node->edges){
			cout << edge->data << " ";
		}
		cout << endl;
	}
}

int main(){
	vector<Vertex*> g = createGraph(5);
	
	// add edges
	addEdge(g[0], g[1]);
	addEdge(g[1], g[2]);
	addEdge(g[2], g[0]);
	addEdge(g[2], g[3]);
	addEdge(g[3], g[4]);
	printGraph(g);
	
	return 0;
}
