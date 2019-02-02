/*
	Design a stack with max functionality. The stack should be able to return the maximum element in O(1).

	Input: numbers for stack
	Output: stack with max api

	Solution:
		To ensure we know about the max element at every instant, we use another stack. That stack tracks the current max element.
		Basically for every push we see if the current top element is greater than the element being pushed or not, if it is
		then we push, else we don't push it. Since any element which occurs after the current max, for it the max is always 
		going to the current max. 

		Now for handling duplicates we need to know their count. This can be done in two ways:
		1.Either we use a stack which int value i.e max and for we see an element which is equal to the top
			then we push it also, so we can account for duplicates. But if our array has only duplicates then it will
			take O(n).
		2. We use a struct {max, freq} as stack element. The freq part is for keeping count of duplicates. Every time a 
			duplicate comes we just decrement its count and for a new push of a duplicate increment its count. But if we have 
			all distinct elements, then we will be using twice the memory compared to way 1.

		TC: O(n), n: no. of elements
		SC: O(n) 
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// class for Max api stack
template <typename T>
class StackWithMaxAPI {
	private:
		// for tracking the max element with its frequency count
		struct MaxTracker {
			T max;
			int freq;
		};

		// stack for keeping track of max
		stack<MaxTracker> maxTracker_;
		// Normal stack for stroing the elements
		stack<T> s_; 

	public:
		// for push
		void Push(T data) {
			s_.emplace(data);

			// first element of stack
			if(maxTracker_.empty()) 
				maxTracker_.emplace(MaxTracker{data, 1});
			// if the current data is greater or equal to max tracker stack
			else if(maxTracker_.top().max <= data) {
				// check if it is a duplicate
				if(maxTracker_.top().max == data) {
					int& count = maxTracker_.top().freq;
					++count;
				}
				else {
					maxTracker_.emplace(MaxTracker{data, 1});
				}
			}			
		}

		// for pop
		T Pop() {
			// check if the stack is empty
			if(s_.empty())
				throw length_error("Stack is empty");
			
			int popped_el = s_.top();
			s_.pop();
			
			// update the max of tracker stack
			if(popped_el == maxTracker_.top().max) {
				int& max_el_count =  maxTracker_.top().freq;
			
				// if this is a duplicate then decrement its count
				if(max_el_count > 1)
					--max_el_count;
				else {
					maxTracker_.pop();
				}
			}
			return popped_el;
		}

		// for max api
		T Max() {
			// throw exception if empty
			if(IsEmpty()) {
				throw length_error("Stack is empty");
			}
			return maxTracker_.top().max;
		}

		// for checking if the stack is empty or not
		bool IsEmpty() const {
			return s_.empty();
		}
};

int main() {
	StackWithMaxAPI<int> el;
	el.Push(1);
	cout << el.Max();
	
	return 0;
}
 