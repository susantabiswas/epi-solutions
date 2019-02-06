/* 
	Given an array of struct elements which contains many with same age. Put the same elements together.
	The elements need not be sorted but same elements should be together. The key for comparison is age provided
	in structure.

	Input: array of elements
	Output: array of elements 

	Solution:
		We need to know the count of each distinct element first. Once we know that, we know how many
		places each element is going to take. We use two hash tables.
		First one stores the count for each key, then for each key we find the first position in array which
		can host them. 
		Then do traversal of array :
			for each element find its position to place, swap positions with that element,
			--count for current obj in hash count table and increase the offest value in the other hash table.
			If the count  == 0, remove the key from hash table
		Once all the keys get over, we have all the keys together.

		If we want the list to be sorted then, we need to have sorted hash table collection, for which we can use 
		BST or map from STL.

		TC: O(n)
		SC: O(m), m: distinct keys
	*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Info{
	int age;
	string name;
};

// brings the objects with similar age key together
vector<Info> bringSimilarTogether(vector<Info> arr) {
	// find the count for each distinct age
	unordered_map<int, int> age_count;
	for(const auto& o: arr) {
		++age_count[o.age];
	}

	// now that count for each age is known, we find the 
	// first position each can take in array
	unordered_map<int, int> array_offset;
	int offset_pos = 0;
	for(const auto& age: age_count) {
		array_offset[age.first] = offset_pos;
		offset_pos += age.second;
	}

	// now place the objects at their correct positions
	while(!array_offset.empty()) {
		// since we are moving them in place, we need to use some clever tricks.
		// we move the element at the current offset position to its correct position
		// we keep doing this and eventually every element will be at their correct position.
		
		// the position where the current age element is supposed to be
		auto to = array_offset.begin();
		// element at that position already stationed
		auto curr = array_offset.find(arr[to->second].age);

		// now move the element already stationed to its correct position 
		// and decrement its count in age_count to indicate that has been placed 
		// and make the offset + 1 for that if the count > 0
		swap(arr[to->second], arr[curr->second]);

		if(age_count[curr->first] > 0) {
			--age_count[curr->first];
			// increment offset
			++array_offset[curr->first];
		}
		// remove the offset for current age key
		if(age_count[curr->first] == 0) {
			// remove the object from hash table
			array_offset.erase(curr->first);
		}
	}

	return arr;
}

ostream& operator<<(ostream& out, vector<Info> arr) {
	for(const auto& a: arr)
		cout << a.name << ", " << a.age << endl;
	cout << endl;
}

int main() {
	vector<Info> arr = {{12, "sam"}, {16, "ram"}, {12, "jon"}, {22, "prince"},
						 {12, "manish"}, {22, "audrey"}, {42, "ramesh"}};
	cout << bringSimilarTogether(arr);
	return 0;
}
