#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;


struct WeightedEdge {
	int x, y;
	int weight;
	WeightedEdge(int x, int y, int weight) : weight(weight), x(x), y(y) {};
};

// Graph node
// To know if edges exists TC: O(V + E) 
struct Vertex {
	int data;
	vector<WeightedEdge> edges;
	Vertex(int data) : data(data), edges(vector<WeightedEdge>{}) {};
};

// Creates a graph node
Vertex* createNode(int data) {
	Vertex* v = new Vertex(data);
	return v;
}

// Adds an edge between two vertices
void addEdge(vector<Vertex*>& g, int src, int dst) {
	g[src]->edges.emplace_back(WeightedEdge(src, dst, 1));
}

// DFS of graph
void dfsHelper(vector<Vertex*>& g, Vertex* curr, unordered_map<Vertex*, bool>& visited) {
	// if the current is visited return
	if (visited.find(curr) != visited.end())
		return;
	// mark current as visited
	visited[curr] = true;
	cout << curr->data << " ";

	// traverse its edges
	for (WeightedEdge edge : curr->edges)
		dfsHelper(g, g[edge.y], visited);
}

// Driver for DFS of graph
// TC: O(V + E)
void DFS(vector<Vertex*>& g) {
	// for marking visited nodes
	unordered_map<Vertex*, bool> visited;
	//start traversal from each vertex to cover disconnet graph case as well
	for (int i = 0; i < g.size(); i++)
		dfsHelper(g, g[i], visited);
}

//BFS of graph
// TC : O(V + E)
void BFS(vector<Vertex*>& g) {
	unordered_map<Vertex*, bool> visited;
	for (int i = 0; i < g.size(); i++) {
		queue<Vertex*> q;
		// add the starting node only if it is not visited yet
		if (visited.find(g[i]) == visited.end())
			q.emplace(g[i]);

		while (!q.empty()) {
			Vertex* curr = q.front();
			q.pop();

			// mark as visited
			visited[curr] = true;
			cout << curr->data << " ";

			// add its next edge nodes
			for (WeightedEdge edge : curr->edges) {
				if (visited.find(g[edge.y]) == visited.end()) {
					q.emplace(g[edge.y]);
				}
			}
		}
	}
}

// prints the graph
void printGraph(vector<Vertex*>& g) {
	for (const Vertex* v : g) {
		cout << v->data << ": ";
		// show the edges
		for (const WeightedEdge edge : v->edges)
			cout << g[edge.y]->data << " ";
		cout << endl;
	}
}

// Creates a graph
vector<Vertex*> createGraph(int n_vertices) {
	vector<Vertex*> g;
	for (int i = 0; i < n_vertices; i++)
		g.emplace_back(createNode(i));
	return g;
}

// deletes the graph
void deleteGraph(vector<Vertex*>& g) {
	for (Vertex* v : g)
		delete v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////	UNION-FIND ////////////////////////////////////////////
/*
	Union-Find with weighted Union and path compression.
	TC: O(logN) for each union-find
*/

class UnionFind {
private:
	// for keeping track of root and size of components
	vector<int> root_;
	vector<int> size_;
public:
	UnionFind(int n_nodes) {
		root_.resize(n_nodes), size_.resize(n_nodes);
		// create the root array and size array
		for (int i = 0; i < n_nodes; i++) {
			root_[i] = i, size_[i] = 1;
		}
	}

	// Finds the root of component
	int getRoot(int idx) {
		// continue DFS till we get a root element
		while (root_[idx] != idx) {
			root_[idx] = root_[root_[idx]];
			idx = root_[idx];
		}
		return idx;
	}

	// Union operation using Weight consideration
	// TC: O(log2N)
	void Union(int a, int b) {
		// find the root of both the elements
		int root_a = getRoot(a);
		int root_b = getRoot(b);

		// based on size of both the components,smaller is the net root is selected
		if (size_[b] < size_[a]) {
			root_[root_b] = root_a;
			size_[root_a] += size_[root_b];
		}
		else {
			root_[root_a] = root_[root_b];
			size_[root_b] += size_[root_a];
		}
	}

	// Find operation using Path Compression
	// TC: O(log2N), N: no. of nodes
	bool Find(int a, int b) {
		// find the roots
		return getRoot(a) == getRoot(b);
	}

	// Returns the no. of connect components
	// prints the number of elements in each component
	void connectedComponents() {
		vector<int> result;
		for (int i = 0; i < root_.size(); i++) {
			if (root_[i] == i)
				result.emplace_back(size_[i]);
		}
		sort(result.begin(), result.end());
		for (const int& a : result)
			cout << a << " ";
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// KRUSKAL'S MINIMUM SPANNING TREE ////////////////////////////////////////
/*
	till edges are there:
		1. pick the smallest weight edge
		2. check if on adding it can cause a cycle or not to the existing edges in MST
		3. repeat step 2
*/


// TC: O(ElogE (sorting) + VlogV(Union-Find for all vertices) )
int kruskalMST(int& vertices, vector<WeightedEdge>& edges) {
	// sort the edges
	sort(edges.begin(), edges.end(),
		[](WeightedEdge a, WeightedEdge b)->bool {
			return a.weight < b.weight;
		});

	// Initialize the Union-Find DS
	UnionFind obj(vertices);
	int cost = 0;
	// pick the edges one by one, making sure of the following:
	// 1. The new edge doesn't create a cycle in the MST, so for
	//    the current edge if the endpoints are already connected
	//    then don't add the edge as it will create a cycle.
	// 2. The edge picked is the smallest in weight possible at the moment 
	for (const WeightedEdge& edge : edges) {
		int src = edge.x;
		int dst = edge.y;
		// check if they are connected or not
		if (!obj.Find(src, dst)) {
			// add the edge to MST
			cost += edge.weight;
			// Since the vertices are connected now, Union them
			obj.Union(src, dst);
		}
	}
	return cost;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// PRIM'S MINIMUM SPANNING TREE ///////////////////////////////////////////
/*
	Here two sets are maintained, one which has all the vertices and other is empty initially

	With each vertex we associate the cut cost
	make starting node's cut cost = 0
	while all the nodes are unvisited:
		pick the vertex with least cut cost, if it is unvisited
		add to mst set
		mark it visited
	inorder to prevent cycle we check if nodes are visited
	TC: O((E+V)logV)
*/

int primMST(int n_vertices, vector<WeightedEdge>& edges) {
	int cost = 0;

	// to track visited vertices
	vector<bool> visited(n_vertices, false);
	// make a min-heap for selecting the smallest edge weight vertex
	priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>>
		min_heap([](const WeightedEdge& a, const WeightedEdge& b)->bool {
			return a.weight > b.weight; 
		});

	// Queue for doing BFS like traversal
	queue<WeightedEdge> q;
	// We start with the root vertex of graph
	//q.emplace();

	return cost;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	vector<Vertex*> g = createGraph(5);

	/*
		0-->1-->2-->3-->4
		^       |
		|_______|
	*/
	// add edges
	addEdge(g, 0, 1);
	addEdge(g, 1, 2);
	addEdge(g, 2, 0);
	addEdge(g, 2, 3);
	addEdge(g, 3, 4);
	printGraph(g);

	cout << "DFS\n";
	DFS(g);
	cout << endl << "BFS\n";
	BFS(g);
	cout << endl;

	// Kruskal's MST
	int n_vertices = 4;
	vector<WeightedEdge> edges = { {0,1,7}, {0,3,6},
									{3,1,9}, {3,2,8},
									{1,2,6} };
	cout << "Kruskal MST cost:" << kruskalMST(n_vertices, edges) << endl;

	// delete the graph to avoid memory leak
	deleteGraph(g);
	return 0;
}

