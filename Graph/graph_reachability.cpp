/*
	Problem: Given an array consisting of outcomes for match played between pairs of teams. 
			Now two teams A and B out of all the teams have been given, find whether we can 
			arrange the teams in such a way that the series start with A and ends with B and each team in 
			the series has beaten the team that comes after that in the series. 
			The outcome is either: win or loss

	Input: Array of outcomes, team A, team B
	Output: bool 
	
	Solution:
		This problem can be thought of as reachibility problem, where we know the source and sink. We
		just need to check whether there is a path from A to B or not. We can use either DFS or BFS for this.
		
	TC: O(E), E: no. of edges
*/


#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<memory>
#include<queue>
using namespace std;

// structure for match outcome
struct MatchResults{
	string winner, loser;
};

// for building the graph from outcome info
unordered_map<string, unordered_set<string>> buildGraph(const vector<MatchResults>& matches){
	// graph
	unordered_map<string, unordered_set<string>> g;
	
	// iterate through the matches
	// we create the edge (u, v) where u is the winning team and v is the losing team
	for(const MatchResults& match: matches){
		g[match.winner].emplace(match.loser);
	}
	
	return g;
}

// for checking whether the graph is reachable from A to B
bool isReachableDFS(const unordered_map<string, unordered_set<string>> &g, const string& curr,
				const string& dest, unordered_set<string>* visited_ptr ){
	// if the dest node has been reached
	if(curr == dest)
		return true;
		
	// keeps track of all the visited nodes
	unordered_set<string>& visited = *visited_ptr;
	
	// first check if the current node has any edges or not
	// and if has already been visited or not
	if(g.find(curr) == g.end() || visited.find(curr) != visited.end()){
		return false;
	}
	
	// make the current node visited
	visited.emplace(curr);
	
	// we will do DFS
	for(const string& team: g.at(curr)){
		if(isReachableDFS(g, team, dest, visited_ptr))
			return true;
	}
	
	return false;
}

// check reachablity using BFS
bool isReachableBFS(const unordered_map<string, unordered_set<string>>& g,
					const string& start, const string& dest, unordered_set<string>* visited_ptr){

	// set reference
	unordered_set<string>& visited = *visited_ptr;
	// required for BFS
	queue<string> q;
	
	// keeps track of current element
	string curr;
	
	// starting element
	q.push(start);
	visited.emplace(start);
	
	while(q.size() > 0){
		curr = q.front();
	
		// remove the node
		q.pop();
		
		// check if the dest has been reached or not
		if(curr == dest){
			return true;
		}
		
		// push all the elements in the same level
		for(const auto node: g.at(curr)){
			// push all the adjacent unvisited nodes
			if(visited.find(node) == visited.end()){
				q.push(node);
				// make it visited
				visited.emplace(curr);
			}
	
		}
	}
	
	return false;						
}

// for checking whether creating such a series is possible or not
bool isPossiblePath(const vector<MatchResults>& matches, const string& A, const string& B, const string& method){
	// create the graph
	unordered_map<string, unordered_set<string>> g = buildGraph(matches);
	
	// check using DFS
	if(method == "DFS")
		return isReachableDFS(g, A, B, make_unique<unordered_set<string>>().get());
	// check using BFS
	else if(method == "BFS")
		return isReachableBFS(g, A, B, make_unique<unordered_set<string>>().get());
}

// prints the graph
void printGraph(const unordered_map<string, unordered_set<string>>& g){
	
	for(const auto it: g){
		cout << it.first << ": ";
		for(const auto inner: it.second){
			cout << inner << " ";
		}
		cout << endl;
	}	
	
}

int main() {
	// match outcomes
	vector<MatchResults> matches = {
									{"A", "C"}, {"C", "D"}, {"C", "E"}, 
									{"D", "A"}, {"E", "D"}, {"B", "D"}
								};
	printGraph(buildGraph(matches));
	cout << isPossiblePath(matches, "A", "B", "DFS");
	cout << endl << isPossiblePath(matches, "A", "B", "BFS");
	return 0;
}
