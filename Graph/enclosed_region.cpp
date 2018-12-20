/*
	Problem: Given a 2D (m X n) matrix with 0 or 1. The aim is find all regions of 0s which are enclosed in 
	the matrix, i.e they cannot reach the boundary of the matrix and make them 1.
	
	NOTE: A node can have edge only with any left, right, front and backward node.
	Input: 2D matrix
	Output: 2D matrix with enclosed 0s flipped to 1s.

	Solution: 
		We can use the inverse of this problem for solving this. It is easier to know the 0s which 
		are touching the boundary than the 0s which are not touching the boundary. We can start doing BFS using
		the boundary 0 nodes and mark the connection 0 nodes as visited.
		After that all those unvisited 0s are comprise the enclosed regions, and we mark them as 1.
		
		TC: O(V + E)
		SC: O(V)
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;


// for storing row, col index
struct Coordinate{
	int x, y;
};


// finds the connected nodes using BFS
void findNodesBFS(vector<vector<int>>& mat, Coordinate start, vector<vector<bool>>* visited_ptr){
	vector<vector<bool>>& visited = *visited_ptr;
	
	const int m = mat.size(), n = mat[0].size();
	
	// for current and next possible node's coordinates
	Coordinate curr, next;
	queue<Coordinate> q;
	
	// add the start node to the queue
	q.push(start);
	// make the current node as visited
	visited[start.x][start.y] = true;
	
	// valid steps
	vector<Coordinate> steps = {
								{1, 0}, 
								{0, 1},
								{-1, 0},
								{0 ,-1}
							};
							
	while(!q.empty()){
		curr = q.front();
		q.pop();
		
		for(const auto step: steps){
			next.x = step.x + curr.x;
			next.y = step.y + curr.y;
			
			// check if the coordinate are valid or not
			// and the node should be 0 also
			if(next.x >= 0 && next.x < m && next.y >= 0 && next.y < n 
				&& !visited[next.x][next.y] && mat[next.x][next.y] == 0)
			{
				// make it viisted and add
				visited[next.x][next.y] = true;
				q.push(next);
			}
		}
	}
}
 
// for finding the enclosed region
void findEnclosedRegion(vector<vector<int>>& mat){
	// for keeping track of visited nodes
	vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size(), false));
	
	const int m = mat.size(), n = mat[0].size();
	// start with the boundary 0s
	// ROWs
	for(int i = 0; i < m; i++){
		// top row
		if(mat[0][i] == 0 && !visited[0][i]){
			findNodesBFS(mat, {0, i}, &visited);
		}
		// bottom row
		if(mat[m-1][i] == 0 && !visited[m-1][i]){
			findNodesBFS(mat, {m-1, i}, &visited);
		}
	}
	
	// COLs
	for(int i = 0; i < n; i++){
		// left column
		if(mat[i][0] == 0 && !visited[i][0]){
			findNodesBFS(mat, {i, 0}, &visited);
		}
		// right column
		if(mat[i][n-1] == 0 && !visited[i][n-1]){
			findNodesBFS(mat, {i, n-1}, &visited);
		}
	}
	
	//  now that all the 0s connected to the boundary 0s have been visited, we
	// can traverse through the matrix once and mark all unvisited 0s as 1.
	for(int i = 1; i < m; i++){
		for(int j = 1; j < n; j++){
			if(mat[i][j] == 0 && !visited[i][j]){
				mat[i][j] = 1;
			}
		}
	}
}

// for printing the matrix
void printMatrix(const vector<vector<int>>& mat){
	for(const auto& row: mat){
		for(const auto& col: row){
			cout << col << " ";
		}
		cout << endl;
	}	
}

int main() {
	vector< vector<int> > mat = {
								{0, 0, 1, 1, 1},
								{0, 1, 1, 0, 1},
								{1, 1, 0, 1, 0},
								{1, 0, 0, 1, 1},
								{0, 1, 0, 1, 1}	
							};
	
	cout << "BEFORE\n";
	printMatrix(mat);
	
	cout <<"\nAFTER\n";
	findEnclosedRegion(mat);
	printMatrix(mat);
	
	return 0;
}
