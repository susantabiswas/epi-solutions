/*
	Given a graph, find whether exists a cycle or not.
	
	Input: Directed graph
	Output: bool
	
	Solution: 
		We can use DFS for this. We associate three states using 3 colors: white,
		grey and black.
		White: initial state
		Grey: Visited once and being processed
		Black: Processed once
		
		We start with white color, then for each node being visited for the first
		time we make it grey and recurse further. Once the call returns back to a 
		node, we make the color for that node as black, indicating that has finished processing.
		While doing DFS we encounter a node which is of grey color, then that means 
		we have a loop in there.
		
*/

#include <iostream>
using namespace std;

int main() {
	
	return 0;
}
