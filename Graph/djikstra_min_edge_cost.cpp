/*
	Given a weighted graph that can be either cyclic/acyclic and directed/undirected. 
	Given a starting and target node, find the min cost path with min number of edges.
	
	Input : Graph g
	Output: min cost 
	
	Solution:
		We can use Djikstra's shortest path algorithm with some modifications.
		For comparing the cost we can include no. of edges also.
*/
#include<iostream>
#include<climits>
#include<vector>
#include<set>
using namespace std;

struct Vertex{
	struct DistanceWithFewestEdges{
		int dist, min_edges;	
	};	
	
	struct VertexWithDistance{
		Vertex& vertex;
		int dist;
	};
	
	DistanceWithFewestEdges distance_fewest_edges = 
		DistanceWithFewestEdges{ numeric_limits<int>::max(), 0};
		
	int id;
	const Vertex* pred = nullptr;
	vector<DistanceWithFewestEdges> edges;
};

// overload comparator
struct Comp{
	bool operator()(const Vertex* lhs, const Vertex* rhs){
		return lhs->distance_with_fewest_edges.distance < rhs->distance_with_fewest_edges.distance ||
		( lhs->distance_with_fewest_edges.distance == rhs->distance_with_fewest_edges.distance &&
		  lhs->distance_with_fewest_edges.min_edges < rhs->distance_with_fewest_edges.min_edges
		);
	}
};

void djikstraShortestPath(Vertex* src, const Vertex* target){
	// make the distance of src 0 
	src->distance_with_fewest_edges = {0, 0};
	// keeps track of unvisited nodes, but instead of filling it initially
	// with all nodes, we put the nodes only when required
	set<Vertex*, Comp> unvisited;
	// start with the source 
	unvisited.emplace(src);
	
	while(!unvisited.empty()){
		// extract the node with shortest distance
		Vertex* u = *unvisited.begin();
		
		// if the node is the target node, then the path has been found
		if(u->id == target->id)
			break;
		unvisited.erase(unvisited.begin());
		
		// relax the adjacent vertex edges
		for(const Vertex::VertexWithDistance& v: u->edges){
			int v_dist = u->distance_with_fewest_edges.dist + v.dist;
			int v_num_edges = u->distance_with_fewest_edges.min_edges + 1;
			
			if(v.vertex.distance_with_fewest_edges.dist > v_dist ||
			(v.vertex.distance_with_fewest_edges.dist == v_dist &&
			v.vertex.distance_with_fewest_edges.min_edges > v_num_edges)){
				// remove the node 
				unvisited.erase(&v.vertex);
				v.vertex.pred = u;
				v.vertex.distance_with_fewest_edges = {v_dist, v_num_edges};
				unvisited.emplace(&v.vertex);
			}
		}
	}
	
	displayShortestPath(target);
}

void displayShortestPath(const Vertex* v){
	if(v){
		displayShortestPath(v->pred);
		cout << v->id << " ";
	}
}

int main() {
	
	return 0;
}
