/*
	Problem: Given a 2D matrix of m X n. The tiles are colored either black or white. Given a position (x, y)
			flip the color of the entire region connected to that point. The region wrt to a point consists
			of all those points that can be reached from that point and have the same color. 
			We can only move forward, backward, left and right.
			
	Input: 2d m X n matrix, (x,y)
	Output: flip the color of the region

	Solution: We can use either BFS or DFS for this problem. We start with the given point and reachout to the
	remaining points which can be reached and flip the colors of those with the same color.
	
	TC: O(mn)
	SC: O(m+n)
*/

#include <iostream>
#include<queue>
#include<vector>
using namespace std;

struct Coordinate{
	// row and col positions.
	// NOTE: not to be confused with horizontal and vertical coordinate system 
	int x, y;	
};

typedef enum { WHITE, BLACK } Color;

// checks if the current step is valid or not positionally
bool isValid(const vector<vector<int>>& arr, const Coordinate& step, 
			const int& m, const int& n){
	// step should lie within bounds of Matrix
	return step.x >= 0 && step.x < m && step.y >= 0 && step.y < n; 
}

// here the color flipping will be done using BFS
void flipColor(vector<vector<int>>& arr, const Coordinate& start){
	
	// matrix dimensions
	const int m = arr.size();
	const int n = arr[0].size();
	
	// for BFS
	queue<Coordinate> q;
	// possible relative neighbor coordinates
	vector<Coordinate> steps = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	// for keeping track of current node
	Coordinate curr;
	// for storing the next possible step
	Coordinate next_step;
	
	// for keeping track of color starting pixel
	Color color = static_cast<Color>(arr[start.x][start.y]);
	
	// start with the starting node
	q.push(start);
	
	while(!q.empty()){
		// take the current element
		curr = q.front();
		q.pop();
		
		// see the adjacent pixels
		for(const auto& step: steps){
			next_step.x = curr.x + step.x;
			next_step.y = curr.y + step.y;
			
			// if the adjacent node is of same color and is a valid position
			if(isValid(arr, next_step, m, n) && arr[next_step.x][next_step.y] == color){
				// add the pixel to the queue and flip the color
				arr[next_step.x][next_step.y] = !color;
				q.push(next_step);
			}
		}
	}
}

void printMatrix(const vector<vector<int>>& arr){
	for(const auto row: arr){
		for(const auto pixel: row){
			cout << pixel << " ";
		}
		cout << endl;
	}	
}

int main() {
	// Input matrix
	vector<vector<int>> arr = {
								{0, 0, 1, 0, 1},
								{0, 0, 0, 0, 0},
								{1, 0, 0, 1, 0},
								{1, 0, 0, 1, 1},
								{0, 1, 0, 0, 0}
							};
	cout << "BEFORE:\n";						
	printMatrix(arr);
	
	cout << "\nAFTER\n";
	flipColor(arr, {0, 4});
	printMatrix(arr);
	
	return 0;
}
