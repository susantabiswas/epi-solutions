/*
	Problem: Given a 2D maze, consisting of Black and white tiles and a starting and destination tile.
	The white tiles are accessable and black ones are not accessable. Check if there exists a path
	from starting tile to the destination tile.
	We can only move forward, backward, left and right.
	Input: 2D matrix 
	Output: bool
	
	Solution: We can use either BFS or DFS for this.
	TC: O(V + E)
	SC: O(V)
*/

#include <iostream>
#include<vector>
#include<queue>
using namespace std;

// tile colors
typedef enum { WHITE, BLACK } TileColor;

// coordinate structure
struct Coordinate{
	// '==' overloader
	bool operator==(const Coordinate& other_coordinate) const{
		return (x == other_coordinate.x && y == other_coordinate.y);
	}
	
	// X: row index and Y: col index
	int x, y;
};

// for printing coordinates
ostream& operator << (ostream& out, const Coordinate& c)
{
    out << "{" << c.x << ", " << c.y << "}";
    return out;
}

// for checking the validity of step
bool isValidStep(const vector<vector<int>>& maze, const Coordinate& step){
	// a step is valid if it is within the maze boundary and it is a white tile
	if( step.y < maze[step.x].size() && step.y >= 0 && step.x >= 0 && step.x < maze.size()
		&& maze[step.x][step.y] == WHITE)
		return true;
	else
		return false;
}


// search using BFS
// for finding the path, we need a queue of paths also till each level. We keep track of paths 
// in a queue originating from different ancestors
bool searchBFS(vector<vector<int>>& maze, const Coordinate& start, const Coordinate& dest, 
				vector<Coordinate>& final_path){
	// for keeping track of nodes
	queue<Coordinate> q;
	// push the starting element
	q.push(start);
	// make it BLACK
	maze[start.x][start.y] = BLACK;
	// for storing the path
	queue<vector<Coordinate>> path;
	// add the starting node to the path
	path.push(vector<Coordinate>{start});
	
	// current node
	Coordinate curr;
	// for keeping track of next step to take
	Coordinate next_step;
	// for keeping track of current path
	vector<Coordinate> curr_path;
	
	// valid steps
	vector<Coordinate> steps = {
								{1, 0}, 
								{0, 1},
								{-1, 0},
								{0 ,-1}
							};
	// do BFS
	while(!q.empty()){
		// take the current node
		curr = q.front();
		// remove the node
		q.pop();
		// current path
		curr_path = path.front();
		path.pop();
		
		if(curr == dest){
			// add the shortest path to the final path
			final_path = curr_path;
			return true;
		}
			
		// add the adjacent nodes
		for(const Coordinate step: steps){
			// next potential node's coordinates
			next_step.x = curr.x + step.x;
			next_step.y = curr.y + step.y;
			
			// check if the step is valid or not
			if(isValidStep(maze, next_step)){
				// make it BLACK
				maze[next_step.x][next_step.y] = BLACK;
				// add the current path with current node to the path queue
				curr_path.push_back(next_step);
				path.push(curr_path);
				curr_path.pop_back();
				// add to queue
				q.push(next_step);
			}
		}
	}
	
	return false;
}
		
				
// for finding the path using DFS
bool searchDFS(vector<vector<int>>& maze, const Coordinate& curr, const Coordinate& dest,
				vector<Coordinate>& path){
	
	// check if it is the dest or not
	if(curr == dest)
		return true;

	// neighbouring nodes can only be the adjacent nodes in 4 directions excluding the diagonals
	const vector< Coordinate > validSteps = {
												{1, 0},
												{0, 1},
												{-1, 0},
												{0, -1}
										};
	// go through the adjacent nodes
	for(const Coordinate step: validSteps){
		// add the next valid node to path
		Coordinate next_step = {curr.x + step.x, curr.y + step.y};
		
		if(isValidStep(maze, next_step)){
			// make it black and add to path
			maze[next_step.x][next_step.y] = BLACK;
			path.push_back(next_step);
			
			if(searchDFS(maze, next_step, dest, path))
				return true;
			// if there is no possible path, then remove the current node
			path.pop_back();
		}
	}
	return false;
}

// driver function for maze searching
vector<Coordinate> mazeSearch(vector<vector<int>>& maze, const Coordinate& start, const Coordinate& dest){
	// for storing the path
	vector<Coordinate> path;
	
	// add the starting tile
	path.emplace_back(start);
	
	// here to keep track of visited nodes, we just make them BLACK
	maze[start.x][start.y] = BLACK;
	// check if there exists a path or not
	if(searchBFS(maze, start, dest, path)){
		return path;
	}
	// remove the starting tile from path since no valid path exists
	path.pop_back();
	maze[start.x][start.y] = WHITE;
	
	return path;	
}

// prints the maze
void printMaze(const vector<vector<int>>& maze){
	for(const auto row: maze){
		for(const auto col_el: row){
			cout << col_el << " ";
		}
		cout << endl;
	}
}

// prints the path
void printPath(const vector<Coordinate>& path){
	if(path.size() > 0){
		cout << "PATH: \n";
		for(const auto node: path)
			cout << node << " ";
		cout << endl;
	}
	else{
		cout << "There is no path for the starting and dest coordinates.";
	}
}

int main() {
	// Input maze
	vector<vector<int>> maze = {
							{0, 0, 1, 0, 1},
							{0, 0, 0, 0, 0},
							{1, 0, 0, 1, 0},
							{1, 0, 0, 1, 1},
							{0, 1, 0, 0, 0}
						};
	
	// start and destination
	Coordinate start{0, 0}, dest{4, 4};
	printMaze(maze);
	// do maze search
	vector<Coordinate> path = mazeSearch(maze, start, dest); 
	
	printPath(path);
	
	return 0;
}
