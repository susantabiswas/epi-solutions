/*
	Given a set of tasks, each requires a fixed time. Now each worker does exactly two tasks. Assign the tasks such that
	all the tasks complete with least amount of time. 
	
	Input: vector of service times
	Output: assignment of tasks with Min waiting time
	
	Solution: 
		Since the tasks with longer duration if paired with larger tasks, makes the total
		time more, so we pair each large task with a smaller task to make the total lesser.
		
		TC: O(nlogn)
*/

#include <iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

// finds the minimum time consuming arrangement of tasks
vector< pair<int, int> > minTimeArrangement(vector<int>& tasks){
	if(tasks.empty())
		return vector<pair<int, int>> {};
	
	vector< pair<int, int> > optArrangment;	
	// sort the tasks
	sort(tasks.begin(), tasks.end());
	
	// pair the largest with the smallest
	for(int i = 0, j = tasks.size()-1; i < j; i++, j--){
		optArrangment.emplace_back(make_pair(tasks[i], tasks[j]));
	}
	
	return optArrangment;
}

int main() {
	vector<int> tasks = {5,22,1,16,4,44};
	
	vector< pair<int, int> > optArrangement = minTimeArrangement(tasks);
	
	for(vector<pair<int, int>>::iterator it = optArrangement.begin();
			it != optArrangement.end(); it++){
		cout << it->first << ", " << it->second << endl;
			}
	return 0;
}
