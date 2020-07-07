/*
	Implement queue with Max API. The queue should be able to return max element currently.
	Input: 
	Output: queue class with Max method 

	Solution:
		We use a second queue which stores the max element currently. Things to note:
		1. Any element which has come before and is greatest will remain the greatest 
			till it is popped.
		2. Any element which comes at a later stage and was not the greatest when it came
			might become the greatest, so we need to keep track of all the elements coming.
		3. If the current element is greater than all the previous elements, then no need of previous elements.
			So we remove the previous elements so that the greatest is always at the front and 
			can be accessed in O(1).
		This is because of the fact that once we get a max element, 
		any element not greater than or equal to after that is not going to be max.
		Since this is FIFO, so the max element should be at front.
		For enqueue:
			Pop elements from tracker queue till the last element is bigger/equal than this
		For dequeue:
			Check if the front of tracker queue is equal to popped element, pop if equal
		For Max:
			return front of tracker queue
			
		TC: enqueue: O(n), for 'n' enqueue operations
			dequeue: O(1)
			max: O(1)
		SC: O(n), n: no. of elements, required for tracking max element 
		 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
using namespace std;

template<typename T>
class Queue {
	private:
		queue<T> q_;
		deque<T> max_tracker_;
	public:
		// for pushing element
		void Enqueue(T data) {
			q_.emplace(data);

			// track the max element
			if(max_tracker_.empty())
				max_tracker_.emplace_back();
			else {
				// pop the elements 
				while(!max_tracker_.empty() && max_tracker_.back() < data){
					max_tracker_.pop_back();
				}
				max_tracker_.emplace_back(data);
			}
		}

		// for popping element
		T Dequeue() {
			if(q_.empty())
				throw length_error("Queue is empty");

			T popped_data = q_.front();
			q_.pop();

			// check if the current element is max also
			if(max_tracker_.front() == popped_data)
				max_tracker_.pop_front();

			return popped_data;
		}

		// checks if queue is empty or not
		bool Empty() {
			return q_.empty();
		}

		// returns the max element
		T Max() {
			if(max_tracker_.empty())
				throw length_error("Queue is empty");	
			return max_tracker_.front();
		}
};

int main() {
	Queue<int> q;

	for(size_t i = 0; i < 6; i++){
		q.Enqueue(i);
		cout << "Max: " << q.Max() << " ";
	}
	cout << endl;
	while(!q.Empty()) {
		cout << "Max: " << q.Max() << " ";
		cout << q.Dequeue() << " ";
	
	}
	
	return 0;
}
 
