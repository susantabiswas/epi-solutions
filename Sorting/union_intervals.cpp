/* 
	Given an array of intervals {start_time, end_time}, the intervals can be merged if they intersect. 
	The endpoints can be open or closed.
	Find the disjoint set of intervals.
	Eg: [1,4), [1,6], (5,6), [5,8] (9,18): [1, 8], (9, 18) 
	
	NOTE: intervals are not sorted
	
	Input: array of intervals 
	Output: array of interval

	Solution:
		
		First we have to sort the intervals by left endpoint. For tie: closed endpoint wins over open. 
		Then after that start with the first interval and from there start the 
		traversal to check if the next interval intersects with it or not. If the intervals
		intersect then take the union of the interval and continue. When at any index the
		interval doesn't intersect then add the union we have recieved till now to the 
		answer and take the current interval as the starting and continue like before.

		TC: O(nlogn)
	*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval{
	// endpoint
	private:
		struct Endpoint{
			bool is_closed;
			int val;
		};
	
	public:
		bool operator<(const Interval& b) const {
			// if the endpoints are same
			if(left.val == b.left.val) {
				return left.is_closed ? true : // if first interval's left is closed then it comes first, doesn't matter if the left of second interval is closed or not, we keep the order stable
						!b.left.is_closed ? true : false; // if the left of first interval is open, then it comes first only 
														// if the left of second interval is also open 
			}
			return left.val < b.left.val;
		}

		Endpoint left;
		Endpoint right;
};


// does union of intervals and returns disjoint set of intervals
vector<Interval> unionIntervals(vector<Interval>& intervals) {
	vector<Interval> disjoint_intervals;
	
	// sort the intervals by left endpoint
	sort(intervals.begin(), intervals.end());
	
	//  resultant interval which is added to the disjoint interval set
	Interval union_interval = intervals[0];
	
	for(int i = 1; i < intervals.size(); i++) {
		// if the current interval intersects with new union_interval
		if( (union_interval.right.val == intervals[i].left.val && 
			(union_interval.right.is_closed || intervals[i].left.is_closed)) ||	// when the left and right points match and atleast either is closed
			union_interval.right.val > intervals[i].left.val // when the left of current interval is before right of union_interval
			) {
			
			// update union_interval's right endpoint
			if((union_interval.right.val < intervals[i].right.val) ||
				(union_interval.right.val == intervals[i].right.val && 
				intervals[i].right.is_closed)) {
				
				union_interval.right = intervals[i].right; 	
			}
		} 
		else { // add the union interval found so far
			disjoint_intervals.emplace_back(union_interval);
			// make the current interval as the starting value for union interval
			union_interval = intervals[i];
		}
	}
	
	// add the last union_interval if left
	disjoint_intervals.emplace_back(union_interval);
	
	return disjoint_intervals;
}

ostream& operator<<(ostream& out, vector<Interval> arr) {
	for(const auto& a: arr)
		cout << (a.left.is_closed?"[":"(") << a.left.val << ", " << a.right.val << (a.right.is_closed?"]":")") << endl;
	cout << endl;
}

int main() {
	// sorted : [1,4), [1,6], (5,6), [5,8], (9,18)
	//      ==> [1, 8], (9, 18) 
	vector<Interval> events = { {{true, 1}, {false, 4}}, 
								{{false, 5}, {false, 6}}, 
								{{true, 1}, {true, 6}}, 
								{{false, 9}, {false, 18}},
								{{true, 5}, {true, 8}}
	};
	
	cout << unionIntervals(events);
	return 0;
}
