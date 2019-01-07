/*
	Given a number of tasks with a fixed service time. A task can only start when the task before it
	completes. Arrange the tasks in such a way that the waiting time is minimum.
	
	Input: vector of service times
	Output: min waiting time
	
	Solution:
		The waiting can be reduced by finishing the tasks with smaller service time. Doing
		this will make the tasks with larger service times wait lesser.
	TC: O(nlogn)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int activitySelection(vector<int>& times){
	int min_time = 0;
	const int n = times.size();
	
	// sort the array of service time
	sort(times.begin(), times.end());
	
	for(int i = 0; i < n; i++){
		min_time += times[i] * (n - i - 1); 
	} 
	
	return min_time;
}

int main() {
	vector<int> times = {12,5,1,2};
	
	int min_time = activitySelection(times);
	cout << min_time ;
	return 0;
}
