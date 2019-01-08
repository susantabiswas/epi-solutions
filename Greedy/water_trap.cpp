/*
	Given an array representing height coordinates and assume their index position
	as the x-coordinate. Find the pair of heights which makes the largest volume for
	trapping water inside.
	
	Input: vector of numbers
	Output: pair of heights
	
	Solution:
		We can get maximum volume by increasing the width and height. Now for having max width we should start 
		with the two end points and for height we need to traverse the heights from both ends and keep
		track of the height that make the maximum volume. We move left if the right side height is lesser than 
		left side, else move right. If the heights are same then move move both end indices.
	TC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the maximum volume of water that can be stored 
int maxWaterVolume(vector<int>& heights){
	int max_vol = 0;
	
	// we traverse from both ends
	int i = 0;
	int j = heights.size() - 1;
	
	while(i < j){
		// check if the current volume is greater than the max volume
		if(((j - i) * min(heights[i], heights[j])) >= max_vol){
			max_vol = (j - i) * min(heights[i], heights[j]);
		}
		
		// check in which direction to move
		if(heights[i] < heights[j])	// move right
			++i;
		else if(heights[i] > heights[j])// move left	
			--j;
		else{
			++i;	// move one step both left and right
			--j;
		}
	}
	
	return max_vol;
}

int main() {
	vector<int> heights = {1,2,1,3,34,4,5,6,2,51,3,1,13,2,1,24,4,1};
	
	cout << maxWaterVolume(heights);
	return 0;
}
