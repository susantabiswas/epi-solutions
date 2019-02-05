/* 
	Given a array of intervals {start_time, end_time}, find the maximum no. of events that are
	happening concurrently.

	Input: array of intervals
	Output: int

	Solution:

		No. of concurrent events at 't': no. of events which have started - no. of evenets that have ended
										N(S) - N(E)
		So to do this, we take out the endpoints and sort them according to time. 
		Same time tie breaker: if one of them is start then that comes first otherwise if
		both are either start or end times, then either or them can come first.

		TC: O(nlogn) 
		SC: O(2n), n: no. of intervals 
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval{
	int start;
	int end;
};

struct Endpoint{
	int time;
	bool is_start;

	bool operator<(const Endpoint& b) const {
		// when the times are diff then whatever comes first
		if(time != b.time) {
			return time < b.time; 
		}
		// when the times are equal, to break the tie
		return is_start && !b.is_start? true :	// if first one is start and other is end 
				!is_start && b.is_start ? false : true; // if first is end and other is start or when both are of same type, let them be
	}

	bool operator==(const Endpoint& b) const {
		return time == b.time;
	}
};

// finds the max no. of concurrent events
int maxConcurrentEvents(vector<Interval>& events) {
	int max_concurrent_events = 0;
	int running_events = 0;
	
	vector<Endpoint> endpoints;
	// first extract the endpoints and sort them
	for(const auto& e: events) {
		endpoints.emplace_back(Endpoint{e.start, true});	// start time endpoint
		endpoints.emplace_back(Endpoint{e.end, false});	// end time endpoint
	}

	sort(endpoints.begin(), endpoints.end());

	// for every start time increment running activity counter and
	// for every end time decrement running activity counter
	for(const auto& e: endpoints) {
		if(e.is_start)
			++running_events;
		else
			--running_events;
			
		// check if the currently running activities are max 
		if(running_events > max_concurrent_events)	
			max_concurrent_events = running_events;
	}
	
	return max_concurrent_events;
}



int main() {
	vector<Interval> events = {{1, 5}, {6, 10}, {11, 13}, {14, 15}, {2, 7}, {4, 15},
								{8, 9}, {13, 15}, {18, 19}};
	
	cout << maxConcurrentEvents(events);
	return 0;
}
