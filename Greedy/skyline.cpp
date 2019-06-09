/*
	Given an array of numbers representing the heights of buildings. Find the
	area of the largest rectangle that can be made out of all these buildings.
	If there is a building of lesser height than the end point buildings then the max height
	for the rectangle is the height of that building.
	
	Input: array of numbers
	Output: Area of largest rectangle
	
	Solution:
		For building 'i' the largest rectangle is the one created by buildings of atleast the same height 
		as the current building on either side. So for each building we need to find the blocking
		building on either sides. 
		So we use a stack and start traversal, if the stack is empty or the current building
		is taller than the last building then we push that because a taller building will not block
		a shorter building.
		When we find a building with smaller height, we keep poping untill the stack top has height lesser 
		than the current building or empty.
	TC: O(n)
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

// finds the largest rectangle area
int findLargestRectangle(vector<int> heights) {
	int max_area = 0;
	int idx = -1;
	int curr_area = 0;
	
	stack<int> buildings;
	
	for(int i = 0; i<heights.size(); i++) {
		// if the height of the current building is higher 
		if(buildings.empty() || heights[buildings.top()] < heights[i]) {
			buildings.push(i);
		}
		else if(heights[buildings.top()] >= heights[i]) {	// when the current height is shorter
			
			// pop the buildings and at the same time compute the largest area for each
			while(!buildings.empty() && heights[buildings.top()] >= heights[i]) {
				// compute area for the current building
				idx = buildings.top();
				buildings.pop();
				// area of largest rectangle supported by this building
				curr_area = heights[idx] * (i - (buildings.empty() ? 0 : buildings.top()+1));
				if(curr_area > max_area) {
					max_area = curr_area;
				}
			}
			
			// push the current building
			buildings.push(i);
		}
	}
	
	// area for the remaining buildings
	while(!buildings.empty()) {
		idx = buildings.top();
		buildings.pop();
		
		curr_area = heights[idx] * (heights.size() - (buildings.empty() ? 0 : buildings.top()+1));
		if(curr_area > max_area)
			max_area = curr_area;
	}
	
	return max_area;
}

int main() {
	vector<int> heights = {1,14,32,54,6,3,42,6,9,2,1,3};
	
	cout << findLargestRectangle(heights);
	return 0;
}
