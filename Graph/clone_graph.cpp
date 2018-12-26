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

// use DFS for cloning the graph
void doDFS(Vertex* u_orig, Vertex* u_copy, vector<Vertex*>& clone, unordered_map<int, Vertex*>& visited){
	// make the node visited
	visited[u_orig->data] = u_copy;
	
	// traverse the adjacent edges 
	// and clone the edges as we go
	for(Vertex* v: u_orig->edges){
		// traverse the node only if it is unvisited
		if(visited.find(v->data) == visited.end()){
			// make a copy of node
			Vertex* v_copy = createNode(v->data);
			// add the node to the cloned graph
			clone.emplace_back(v_copy);
		
			// do DFS 
			doDFS(v, v_copy, clone, visited);
		}
		// create a copy of edge
		u_copy->edges.push_back(visited[v->data]);
	}
}

// use BFS for cloning the graph
void doBFS(){
	
}

// for cloning the graph
vector<Vertex*> cloneGraph(Vertex* u){
	// create the root node
	vector<Vertex*> clone;
	// for keeping track of visited nodes,
	// we map each label node to their address
	unordered_map<int, Vertex*> visited;
	
	// make a copy of root node
	Vertex* u_copy = createNode(u->data);
	// add the node to the cloned graph
	clone.emplace_back(u_copy);
	
	// for cloning we can use either BFS or DFS
	doDFS(u, u_copy, clone, visited);
	
	return clone;
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
	cout << endl << endl;
	
	vector<Vertex*> cloned_graph = cloneGraph(g[0]);
	printGraph(cloned_graph);
	return 0;
}
