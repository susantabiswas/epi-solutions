/*
	Given a set of tasks with starting and ending time. Each task is represented as [start, end].
	Now we need to check if the status of each task by visiting it at that time. We can check the
	status by visiting at any time between the closed interval of that task and also we 
	can check other tasks lying in that interval. Find the min number of times one should visit
	so as to cover all tasks.
	
	Input: array of [start, end] tasks
	Output: Min number of visits(int)
	
	Solution:
		The task which starts before every task needs to be visited. Now we can visit the task at the end time 
		instead of visiting it at the start time, now all the tasks that start between the closed interval of
		that task can be visited. Again we look for the first task whose starting time isn't covered in the
		closed interval and we select its end time as visit time. Do the same for the remaining tasks.
	
	TC: O(nlogn)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// calculates the minimum number of visits required for covering the entire set of tasks
vector<int> calculateMinVisits(vector<pair<int, int>>& tasks){
	// sort the 
	sort(begin(tasks), end(tasks), 
		[](const pair<int, int>& t1, const pair<int, int>& t2)->bool{
			return t1.second < t2.second;		
		}
	);
	
	// for keeping track of visits made
	vector<int> visits;
	// first visit will be end time of first sorted task
	visits.emplace_back(tasks.front().second);
	
	for(int i = 1; i < tasks.size(); i++){
		// if the starting time of current task is lesser than the 
		// last time visited, then that can be covered, since its end time will happen after the 
		// the last visited time .
		if(tasks[i].first > visits.back()){
			// push the current task's end time as visiting time
			visits.emplace_back(tasks[i].second);
		}
	}
	
	return visits;
}

int main() {
	vector<pair<int, int>> tasks = {{2, 5}, {3, 6}, {1, 4}, {7, 8}};
	
	vector<int> visits = calculateMinVisits(tasks);
	
	for(auto visit: visits){
		cout << visit << " " ;
	}
	return 0;
}
