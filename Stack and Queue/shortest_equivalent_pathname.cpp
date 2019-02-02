/*
	Given a working path for file system. Find the shortest equivalent path for that.
	eg: /d1/./../d2 equivalent to /d2
	Input: string
	Output: string

	Solution:
		A path can start with '/', so first '/' shouldn't be ignored. Now for every '.' we ignore it, since it means current dir only
		For every '..' we can just remove the last dir if avail and ignore it else it there is no dir before it then
		keep it. It might mean a relative path.
		Note: if '..' appears after '/' then it is not possible to go before the root '/', so it won't be allowed
		TC: O(n), n: no. of elements
		SC: O(n) 
*/

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <sstream>
using namespace std;

// finds the shortest equivalt path for a given input path
string shortestEquivalentPath(const string& dir_path) {
	if(dir_path.empty())
		throw length_error("Empty path");
		
	// string stream
	stringstream ss(dir_path);
	string token;
	const char delimiter = '/';

	// for storing the filtered path
	deque<string> path;

	// root case: if the path starts from root then '/' shouldn't be ignored
	if(dir_path.front() == '/')
		path.emplace_back("/");

	while(getline(ss, token, delimiter)) {
		// if token is other than "." and ".." and not empty add
		if(token != "" && token != "." && token != "..") {
			path.emplace_back(token);
		}
		else if(token == "..") {
			// if there is nothing before this or again ".."
			// then just add it
			if(path.empty() || path.back() == "..")
				path.emplace_back(token);
			else {
				// if last token was root "/", then we can't go up to parent
				if(path.back() == "/")
					throw invalid_argument("Wrong path\n");
				else {	// if there is a parent dir then remove that
					path.pop_back();
				}
			}
		}
	}

	if(path.empty())
		return "";
		
	// now add "/" between each term, ensuring that if the path starts with
	string shortest_path;
	deque<string>::iterator it = path.begin();
	// add the root term
	shortest_path = *it;
	++it;	//second term
	// if first term was '/' then we dont add another '/'
	if(shortest_path == "/"){
		shortest_path += *it;
		++it;
	}
	
	for(; it != path.end(); it++) {
		shortest_path += "/" + *it;
	}

	return shortest_path;
}

int main() {
	string dir_path = "./../";
	cout << shortestEquivalentPath(dir_path);
	return 0;
}
 
