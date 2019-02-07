/* 
	Given a list of coordinates for points in 2D plane. Find the 'k' closest points from origin.
  

	Input: vector of int, int k
	Output: 1d sorted vector
	
	Solution:
		We can traverse through the coordinates and calculate the distance from origin while we go.
		Since we need to find the closest points that means we need to find the 'k' smallest distance 
		points, we can use a max-heap of size 'k' for that. 
		Since it is a max-heap it will be removing the maximum element everytime when we are doing traversal
		from the coordinates.

		TC: O(nlogk), k: heap size, n: no. of elements
		SC: O(k) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <sstream>
#include <functional>
using namespace std;

struct Point{
	double dist;	// distance from origin
	int x, y;	// coordinates

	bool operator<(const Point& p) const {
		return dist < p.dist;
	}
};

// for each coordinate 
struct Coordinate{
	int x, y;
};

// calculates distance between given point to origin
double getDistance(const Coordinate& pt) {
	return sqrt(pt.x * pt.x + pt.y * pt.y);
}

// finds the k closest coordinates 
vector<Coordinate> findKClosestPoints(const vector<Coordinate>& pts, int k) {
	// make a max-heap 
	priority_queue<Point, vector<Point>> max_heap;
	
	for(int i = 0; i < pts.size(); i++) {
		max_heap.emplace( Point{
			getDistance(pts[i]), pts[i].x, pts[i].y}
		);

		// if the size is greater than k, pop the farthest coordinate
		if(max_heap.size() > k)
			max_heap.pop();
	}
	
	vector<Coordinate> k_closest_pts;
	
	while(!max_heap.empty()) {
		auto pt = max_heap.top();
		k_closest_pts.emplace_back(Coordinate{pt.x, pt.y});
		max_heap.pop();
	}
	
	return k_closest_pts;
}

// overloading << for directly viewing the vector elements
template<typename T>
ostream&  operator<<(ostream& out, vector<T> arr) {
	for(const auto& a: arr)
		cout << a.x << ", " << a.y << endl;
	cout << endl;
}

int main() {
	vector<Coordinate> pts = {{-1, -0}, {5, 5}, {2, 3}, {9, 9}, {1, 0}};					
	cout << findKClosestPoints(pts, 2);
	return 0;
}
