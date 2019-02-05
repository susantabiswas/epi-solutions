/* 
	Given two sorted arrays. Return a vector which contains only the intersection of the arrays. The intersection shouldn't 
	contain any duplicates even if the array have them.

	Input: two int sorted arrays
	Output: array of intersection

	Solution:
		Since the arrays are sorted we can just use two index var for the two arrays and start traversal till 
		one of them is finished. In every iteration we check :
			Increment index for the array with smaller value
			If the values are same, then add to intersection array and increment both index
		TC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

// finds the intersection of two sorted arrays
vector<int> findIntersection(const vector<int>& a, const vector<int>& b) {
	vector<int> intersection;
	int i = 0, j = 0; //i is for vector 'a' and j is for vector 'b'

	// traverse till one of them finishes
	while(i < a.size() && j < b.size()) {
		// if the values are same, then add
		if(a[i] == b[j]) {
			intersection.emplace_back(a[i]);
			++i, ++j;
		}
		else if(a[i] < b[j])
			++i;
		else if(a[i] > b[j])
			++j;
	}

	return intersection;
}

ostream& operator<<(ostream& out, vector<int> arr) {
	for(const auto& a: arr)
		cout << a << " ";
	cout << endl;
}

int main() {
	vector<int> a = {2, 3, 6, 8, 22, 23, 23, 78, 99};
	vector<int> b = {6, 6, 23, 99};

	cout << findIntersection(a, b);
	return 0;
}
