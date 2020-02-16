#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

// Weighted Edge of graph
struct WeightedEdge {
	int start, end;
	int weight;
	WeightedEdge(int start, int end, int weight) : weight(weight), start(start), end(end) {};
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
void addEdge(vector<Vertex*>& g, int src, int dst, int weight = 1) {
	g[src]->edges.emplace_back(WeightedEdge(src, dst, weight));
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
		dfsHelper(g, g[edge.end], visited);
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
				if (visited.find(g[edge.end]) == visited.end()) {
					q.emplace(g[edge.end]);
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
			cout << g[edge.end]->data << " ";
		cout << endl;
	}
}

// prints the Minimum Spanning Tree
void printMST(vector<vector<WeightedEdge>>& mst) {
	for (int i = 0; i < mst.size(); i++) {
		cout << i << ": ";
		// show the edges
		for (const WeightedEdge& edge : mst[i])
			cout << edge.end << "(" << edge.weight << "), ";
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
/*
	TOPOLOGICAL SORTING
	TC: O(V + E)
	SC: O(V + E)

	Gives ordering of vertices such that all the source vertices 
	come before the destination vertices for edges.

	The idea is to do a modified DFS. Instead of processing the current
	vertex, go recurse for its adjacent neighbours whic are unvisited. This
	way the parent node will be printed in the end.

	To detect cycle we keep track of vertices in the recursion stack of current branch.
*/

// Modified version of DFS
void topologicalSortDFS(int src, vector<Vertex*>& g,
	deque<int>& order, vector<bool>& visited) {
	// mark it visited
	visited[src] = true;

	// do DFS for its neighbours
	for (const WeightedEdge& edge : g[src]->edges) {
		if(!visited[edge.end])
			topologicalSortDFS(edge.end, g, order, visited);
	}
	// add to order
	order.emplace_back(src);
}

vector<deque<int>> allTopologicalSortOrders(vector<Vertex*>& g) {
	const int n_vertices = g.size();
	stack<Vertex*> s;
	// for storing the topological order
	vector<deque<int>> all_orders;
	
	// topological sorting from each vertex
	for (int i = 0; i < n_vertices; i++) {
		// stores a topological order
		deque<int> order;
		// for keeping track of visited nodes
		vector<bool> visited(n_vertices, false);
		visited[i] = true;
		topologicalSortDFS(i, g, order, visited);
		all_orders.emplace_back(order);
	}
	
	return all_orders;
}

// DFS Helper
// Returns true in case of cycle else false
bool topologicalDFS(int curr, vector<Vertex*>& g, vector<int>& order,
	vector<bool>& rec_stack, vector<bool>& visited) {
	// current is visited means, topological ordering from current node
	// must already be added, so we can safely ignore the remaining vertices from here on
	if (visited[curr])
		return false;
	// mark the current as visited
	visited[curr] = true;
	// add to recursion stack
	rec_stack[curr] = true;

	// DFS for its neighbours
	for (const WeightedEdge& edge: g[curr]->edges) {
		// if current is already visited, that means there is a cycle
		if (rec_stack[edge.end])
			return true;
		else if (topologicalDFS(edge.end, g, order, rec_stack, visited))
			return true;
	}
	// make the current node of branch unvisited
	rec_stack[curr] = false;
	// add the current in the order after processing its neighbours
	order.emplace_back(curr);

	return false;
}

// Using DFS
// TC: O(V + E)
vector<int> topologicalDFS(vector<Vertex*>& g) {
	// for tracking visited vertices
	vector<bool> visited(g.size(), false);
	// for keeping track of vertices in recursion stack
	vector<bool> rec_stack(g.size(), false);
	vector<int> order;
	// in case of disconnected graph
	for (int i = 0; i < g.size(); i++)
		if (!visited[i])
			// if there is a cycle return empty order
			if (topologicalDFS(i, g, order, rec_stack, visited))
				return vector<int>{};
	return order;
}

// Using BFS
// TC: O(V + E)
vector<int> topologicalBFS(vector<Vertex*>& g) {
	vector<int> order;
	// to keep track of visited vertices
	int visited_vertices = 0;

	// find the indegree of vertices
	vector<int> indegree(g.size(), 0);
	for (int i = 0; i < g.size(); i++)
		for (const WeightedEdge& edge: g[i]->edges)
			++indegree[edge.end];

	queue<int> q;
	// add the 0 indegree vertices
	for (int i = 0; i < indegree.size(); i++)
		if (indegree[i] == 0)
			q.emplace(i);

	while (!q.empty()) {
		int curr = q.front();
		order.emplace_back(curr);
		q.pop();
		++visited_vertices;

		// decrement the indegree of its neighbours
		for (const WeightedEdge& edge : g[curr]->edges) {
			--indegree[edge.end];
			if (indegree[edge.end] == 0)
				q.emplace(edge.end);
		}
	}

	// return the order in reverse 
	reverse(order.begin(), order.end());
	return visited_vertices < g.size() ? vector<int>{} : order;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///					BOTH PRIM AND KRUSKAL'S ALGO WORK ONLY FOR UNDIRECTED CONNECTED GRAPHS 
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// KRUSKAL'S MINIMUM SPANNING TREE ////////////////////////////////////////
/*
	till edges are there:
		1. pick the smallest weight edge
		2. check if on adding it can cause a cycle or not to the existing edges in MST
		3. repeat step 2
*/


// TC: O(ElogE (sorting) + VlogV(Union-Find for all vertices) )
vector<vector<WeightedEdge>> kruskalMST(int& n_vertices, vector<WeightedEdge>& edges) {
	// stores the MST
	vector<vector<WeightedEdge> > mst(n_vertices);
	// sort the edges
	sort(edges.begin(), edges.end(),
		[](WeightedEdge a, WeightedEdge b)->bool {
			return a.weight < b.weight;
		});

	// Initialize the Union-Find DS
	UnionFind obj(n_vertices);
	int cost = 0;
	// pick the edges one by one, making sure of the following:
	// 1. The new edge doesn't create a cycle in the MST, so for
	//    the current edge if the endpoints are already connected
	//    then don't add the edge as it will create a cycle.
	// 2. The edge picked is the smallest in weight possible at the moment 
	for (const WeightedEdge& edge : edges) {
		int src = edge.start;
		int dst = edge.end;
		// check if they are connected or not
		if (!obj.Find(src, dst)) {
			// add the edge to MST
			cost += edge.weight;
			mst[src].emplace_back(edge);
			// Since the vertices are connected now, Union them
			obj.Union(src, dst);
		}
	}
	cout << "Kruskal MST cost:" << cost << endl;
	return mst;
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
	TC: O((E)logE)
*/

vector<vector<WeightedEdge>> primMST(vector<Vertex*>& g) {
	int cost = 0;
	int n_vertices = g.size();
	// stores the MST
	vector<vector<WeightedEdge> > mst(n_vertices);

	// to track visited vertices
	vector<bool> visited(n_vertices, false);
	// make a min-heap for selecting the smallest edge weight vertex
	priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>>
		min_heap([](const WeightedEdge& a, const WeightedEdge& b)->bool {
		return a.weight > b.weight;
			});

	// we start with the first node
	visited[0] = true;
	// add all its neighbours
	for (WeightedEdge& edge : g[0]->edges)
		min_heap.emplace(edge);

	// We add only the edge with min weight that connects a vertex,
	// NOTE: We have no control over the edges connecting the same vertex
	// while adding to heap, so for popping check if it was visited
	while (!min_heap.empty()) {
		WeightedEdge curr = min_heap.top();
		min_heap.pop();

		// add the edge iff the end vertex has not been visited so far
		if (!visited[curr.end]) {
			// mark the current as visited
			visited[curr.end] = true;

			// add to MST
			mst[curr.start].emplace_back(curr);
			cost += curr.weight;
			// add its non visited neighbours
			for (WeightedEdge& edge : g[curr.end]->edges) {
				if (!visited[edge.end]) {
					min_heap.emplace(edge);
				}
			}
		}
	}

	cout << "Prim's cost:" << cost << endl;
	return mst;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// SHORTEST PATH ALGORITHM //////////////////////////////////////////
void printDistances(vector<int>& distance) {
	for (int i = 0; i < distance.size(); i++) {
		cout << "[" << i << "]: " << distance[i] << endl;
	}
}

// Prints distance between all the vertex pairs
void printAllDistances(vector<vector<int>>& distance) {
	for (int i = 0; i < distance.size(); i++) {
		cout << "[" << i << "]: ";
		for (const auto& a : distance[i]) {
			cout << (a == INT_MAX ? "INF" : to_string(a)) << " ";
		}
		cout << endl;
	}
}
///////////////////////////////////////// BELLMAN FORD ///////////////////////////////////////////
/*
	Used for finding the shortest path from a SOURCE vertex to all other vertices.

	USE: Used for finding the existence of negative cycles.

	The idea is to do relaxation for all the vertices. Since there can't be any cycles
	so we can have maximum of V-1 edges, otherwise there will be cycle.

	1. select source SRC
	dist[V] = INF
	dist[SRC] = 0

	for [1:V-1]:
		for each edge a->b:
			if W + dist[a] < dist[b]:
				update the dist[b]

	check for existence of negative cycle
	for [0:V-1]:
		for each edge a->b:
			if W + dist[a] < dist[b]:
				report the negative cycle

	TC: O(EV)
*/

vector<int> bellmanFord(vector<Vertex*>& g, int src) {
	const int N_VERTICES = g.size();
	// initially distance of all the vertices from source is Infinity
	vector<int> dist(N_VERTICES, numeric_limits<int>::max());

	// distance of source vertex is source to reach 
	dist[src] = 0;

	// find the shortest distance using relaxation
	for (int i = 0; i < N_VERTICES - 1; i++) {
		// traverse through all the edges 
		// TC: O(V + E)
		for (const Vertex* v : g) {
			for (const WeightedEdge edge : v->edges) {
				int start = edge.start;
				int end = edge.end;

				// update the shortest distance if the current 
				// weight makes the path shorter
				if (edge.weight + dist[start] < dist[end]) {
					dist[end] = edge.weight + dist[start];
				}
			}
		}
	}

	// check for negative cycle
	for (const Vertex* v : g) {
		for (const WeightedEdge& edge : v->edges) {
			int start = edge.start;
			int end = edge.end;

			// if the current weight still makes the path shorter implies
			// there is negative weight
			if (edge.weight + dist[start] < dist[end]) {
				cout << "Negative cycle in " << start << "---" << edge.weight << "---->" << end << endl;
			}
		}
	}
	return dist;
}

///////////////////////////////////////// DJIKSTRA ///////////////////////////////////////////////
/*
	Shortest distance between source vertex SRC to target vertex.
	NOTE: Doesn't work with negative weights.
	TC: O(V + ElogV)

	1. set the distance for all the vertices as INF
	2. dist[src] = 0
	3. add the neighbouring vertices with their distance from source
	while min heap is not empty:
		take the current vertex with dist and update its
		neighbouring vertex dist if current has not been visited
*/
vector<int> djikstra(vector<Vertex*>& g, int src, int target) {
	const int n_vertices = g.size();
	// for keeping track of visited vertices
	vector<bool> visited(n_vertices, false);
	// distance(i): distance from source vertex
	vector<int> distance(n_vertices, numeric_limits<int>::max());
	
	// source distance is always zero
	distance[src] = 0;
	
	// Vertex with its weight from its parent
	struct WeightedVertex {
		int label;
		int distance = 0;
		WeightedVertex(int label, int distance) : label(label), distance(distance) {};
	};

	// min-heap for getting the shortest weight vertex
	priority_queue < WeightedVertex, vector<WeightedVertex>,
					function<bool(WeightedVertex, WeightedVertex)>>
		min_heap([](const WeightedVertex& a, const WeightedVertex& b)->bool {
			return a.distance > b.distance;
		});

	// push the starting source
	min_heap.emplace(WeightedVertex(src, 0));

	while (!min_heap.empty()) {
		WeightedVertex curr = min_heap.top();
		min_heap.pop();

		// if current is not visited, update the distacne of its neighbours
		if (!visited[curr.label]) {
			// mark it visited
			visited[curr.label] = true;
			// if current is the target return, or continue if 
			// you want the shortest distance for all the vertices
			if (curr.label == target)
				break;
			for (WeightedEdge& edge : g[curr.label]->edges) {
				// update the path distance and push the neighbouring vertex distance iff it is unvisited
				if (!visited[edge.end] && edge.weight + distance[curr.label] < distance[edge.end]) {
					distance[edge.end] = edge.weight + distance[curr.label];
					min_heap.emplace(WeightedVertex(edge.end, distance[edge.end]));
				}
			}
		}
	}

	return distance;
}

//////////////////////////////////////// FLOYD WARSHALL //////////////////////////////////////////
/*
	All pair shortest distance.
	TC: O(V^3)

	This is a DP based solution, we use V x V states and find the min distance
	between i and j using:
	dist(i, j) = min(dist(i, j), dist(i, k) + dist(k,j)), i<=k<=j
*/

vector<vector<int>> floydWarshall(vector<Vertex*>& g) {
	int n_vertices = g.size();
	// dp(i, j): shortest distance between vertex i and vertex j
	vector<vector<int>> distance(n_vertices, vector<int>(n_vertices, INT_MAX));
	
	// put the initial distance between vertices using the edge weights
	for (const Vertex* v : g) {
		for (const WeightedEdge& edge : v->edges) {
			int start = edge.start;
			int end = edge.end;

			distance[start][end] = edge.weight;
		}
	}
	// distance between the same vertex is zero
	for (int i = 0; i < n_vertices; i++)
		distance[i][i] = 0;

	printAllDistances(distance);
	for (int k = 0; k < n_vertices; k++) {
		for (int i = 0; i < n_vertices; i++) {
			for (int j = 0; j < n_vertices; j++) {
				// update the distance if the current distance till kth vertex and beyond is lesser
				if (((distance[i][k] == INT_MAX ||  distance[k][j] == INT_MAX) ? INT_MAX : distance[i][k] + distance[k][j]) < distance[i][j])
					distance[i][j] = distance[i][k] + distance[k][j];
			}
		}
	}
	cout << endl;
	return distance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
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
	/*
		{0}----------7--------
		|                    |
		6                    |
		|                    |
		--->{3}---9---->{1}<--
			|             |
			8             6
			|             |
			-------->{2}<--
	*/
	vector<Vertex*> g1 = createGraph(n_vertices);
	addEdge(g1, 0, 1, 7);
	addEdge(g1, 0, 3, 6);
	addEdge(g1, 3, 1, 9);
	addEdge(g1, 3, 2, 8);
	addEdge(g1, 1, 2, 6);

	vector<WeightedEdge> edges = { {0,1,7}, {0,3,6},
									{3,1,9}, {3,2,8},
									{1,2,6} };
	auto mst_kruskal = kruskalMST(n_vertices, edges);
	printMST(mst_kruskal);
	cout << endl;
	// Prim's MST
	auto mst_prim = primMST(g1);
	printMST(mst_prim);

	// Bellman Ford shortest path
	/*
		{0}----------4--------
		|                    |
		3                    |
		|                    |
		--->{2}         {1}<--
			|             |
		   -2             7
			|             |
			-------->{3}<--
	*/
	vector<Vertex*> g2 = createGraph(4);
	addEdge(g2, 0, 1, 4);
	addEdge(g2, 0, 2, 3);
	addEdge(g2, 1, 3, 7);
	addEdge(g2, 2, 3, -2);
	cout << "Bellman Ford:\n";
	auto distances = bellmanFord(g2, 0);
	printDistances(distances);

	// Djikstra shortest path
	/*
		{0}----------4--------
		|                    |
		3                    |
		|                    |
		--->{2}         {1}<--
			|             |
		    2             7
			|             |
			-------->{3}<--
	*/
	int src = 0, target = 3;
	vector<Vertex*> g3 = createGraph(4);
	addEdge(g3, 0, 1, 4);
	addEdge(g3, 0, 2, 3);
	addEdge(g3, 1, 3, 7);
	addEdge(g3, 2, 3, 2);
	cout << "\nDjikstra: \nSource: " << src << ", Target: " << target << endl;
	distances = djikstra(g3, 0, 3);
	printDistances(distances);

	cout << "\nFloyd Warshall:\n";
	auto all_distances = floydWarshall(g3);
	printAllDistances(all_distances);


	// Topological sort 

	// finds all the topological sort orders
	auto topological_order = allTopologicalSortOrders(g3);
	cout << "\nTopological Sorting Orders:\n";
	for (const auto& order : topological_order) {
		for (auto it = order.rbegin(); it != order.rend(); it++)
			cout << *it << " ";
		cout << endl;
	}

	auto order = topologicalBFS(g3);
	cout << "\nBFS Topological Sorting:\n"; 
	for (auto it = order.rbegin(); it != order.rend(); it++)
		cout << *it << " ";
	cout << endl;

	order = topologicalDFS(g3);
	cout << "\nDFS Topological Sorting:\n";
	for (auto it = order.rbegin(); it != order.rend(); it++)
		cout << *it << " ";
	cout << endl;

	// delete the graph to avoid memory leak
	deleteGraph(g);
	deleteGraph(g1);
	deleteGraph(g2);
	deleteGraph(g3);
	return 0;
}
