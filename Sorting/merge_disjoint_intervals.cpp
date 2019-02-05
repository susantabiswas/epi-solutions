/* 
	Given an array of intervals {start_time, end_time}, each interval is disjoint with the other. Given an input interval,
	return the update disjoint set of intervals. eg: <1,4>, <5,6>, <7,8> and input:<2,6>: <1,6>, <7,8>
	The array is sorted acc to starting time of each interval

	Input: array of intervals and interval
	Output: array of interval

	Solution:
		First add intervals before the input interval, once we get an intersecting interval, then take the union.
		Continue doing that. If we get an interval not intersecting add it.

		TC: O(n)
	*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval{
	int start;
	int end;
};

// checks if the intervals are intersecting or not
bool isIntersecting(Interval& a, Interval& b) {
	return (a.end <= b.end && a.end >= b.start) ||
			(b.end <= a.end && b.end >= a.start);
}

// merges the disjoint interval set
vector<Interval> mergeDisjointIntervals(vector<Interval>& intervals, Interval& new_interval) {
	vector<Interval> disjoint_intervals;
	int i = 0;
	// add all the non-intersecting intervals
	while(i < intervals.size() && !isIntersecting(intervals[i], new_interval))
		disjoint_intervals.emplace_back(intervals[i++]);

	// find the interval upper and lower bounds for the new merged interval
	while(i < intervals.size() && isIntersecting(intervals[i], new_interval)) {
		new_interval = Interval{min(intervals[i].start, new_interval.start), 
							max(intervals[i].end, new_interval.end)};
		++i;
	}
	
	// add the updated interval
	disjoint_intervals.emplace_back(new_interval);
	
	// add all the non-intersecting intervals
	while(i < intervals.size() && !isIntersecting(intervals[i], new_interval))
		disjoint_intervals.emplace_back(intervals[i++]);
		
	return disjoint_intervals;
}  

ostream& operator<<(ostream& out, vector<Interval> intervals) {
	for(const auto& interval: intervals)
		cout << "<" << interval.start << ", " << interval.end << ">\n";
	cout << endl;
}

int main() {
	vector<Interval> intervals = {{-22, -1}, {1, 5}, {6, 10}, {11, 13}, {14, 15}};
	Interval new_interval = {2, 13};
	cout << mergeDisjointIntervals(intervals, new_interval);
	return 0;
}
