/* 
	Given an array which contains names in the form of <first_name, last_name>. Remove the duplicate 
	first name entries. Second name doesn't matter for those cases.

	Input: array of names
	Output: name array without first name duplicates

	Solution:
		We sort the array acc. to first name, then again do one travesal and remove
		the duplicate first names.
		
		TC: O(nlogn)
		SC: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Name{
	string first;
	string last;
/*	
	bool operator<(const Name& b) const {
		if(first != b.first)
			return first < b.first;
		
		return last < b.last; 
	}
	
	bool operator==(const Name& b) const {
		return first == b.first;
	}*/
};

// removes first name duplicates
vector<Name> removeFirstNameDuplicates(vector<Name>& names) {
	// sort the array according to first name
	// NOTE: we can do this without the lambda function also, since the operators have 
	// been overloaded for this structure already
	sort(names.begin(), names.end(), [](const Name& a, const Name& b) -> bool{
		if(a.first != b.first)
			return a.first < b.first;
		return a.last < b.last;
	});
	
	// index where the current name can be put
	int write_idx = 0;
	/*
		We use two indices. First tracks the last name written, second 
		tracks the current names. If the current name is a duplicate we don't increment
		first index otherwise we write the current name at the next index of first index and
		increment the first index 
	 */
	
	// start traversal and remove the duplicate entries
	for(int i = 1; i < names.size(); i++) {
		if(names[write_idx].first != names[i].first)
			names[++write_idx] = names[i++];
	}
	return vector<Name>{names.begin(), names.begin() + write_idx + 1};
}


ostream& operator<<(ostream& out, vector<Name> arr) {
	for(const auto& a: arr)
		cout << a.first << " " << a.last << endl;
	cout << endl;
}

int main() {
	vector<Name> names = {{"jon", "snow"}, {"sam", "khanna"}, {"jon", "oliver"}, 
					{"ravi", "snow"}, {"ravi", "raju"}};
	cout << removeFirstNameDuplicates(names);
	return 0;
}
