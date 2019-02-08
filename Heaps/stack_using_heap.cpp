/* 
	Implement Stack using Heap

	Input: 
	Output: Stack class
	
	Solution:
		Since the main thing about stack is the LIFO, so need to track the last element somehow.
		Now using heap we can track the largest or the smallest in O(1), so we need to do something about
		the recent elements of stack such that they come to root of heap.
		So we associate each element a counter number, we increment it with each element.
		So the most recent will have the largest count and using a max-heap it will be always on
		top.

		Similarly if we use a min heap we can implement a queue.

		TC: O(logn), for push and pop 
		SC: O(n) for heap
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

// Stack class using Heap
template<typename T>
class Stack{
	private:
		struct HeapElement{
			int priority_val;
			T data;
			
			bool operator<(const HeapElement& b) const {
				return priority_val < b.priority_val;
			}
		};

		// counter variable
		int priority_ = 0;
		
		// max-heap 
		priority_queue<HeapElement, vector<HeapElement>, less<>> max_heap_;
			/*max_heap_([](const HeapElement& a, const HeapElement& b)->bool {
					return a.priority_val < b.priority_val; 
			});*/

	public:
		// for pushing element
		void Push(T data) {
			max_heap_.emplace(HeapElement{priority_, data});
			// increment the priority value for next element
			++priority_;
		}

		// for popping element
		T Pop() {
			// if stack is empty
			if(max_heap_.empty())
				throw length_error("Stack is empty");
			else {
				HeapElement el = max_heap_.top();
				max_heap_.pop();
				return el.data;
			}
		}

		// for checking if stack is empty
		bool Empty() {
			return max_heap_.empty();
		}

		// for lookup of top element
		T Top() {
			// if stack is empty
			if(max_heap_.empty())
				throw length_error("Stack is empty");
			else {
				return max_heap_.top().data;
			}
		}
};


int main() {
	Stack<int> s;
	for(int i = 0; i<8; i++)
		s.Push(i);
	cout << s.Pop() << endl;
	cout << s.Top() << endl;
	cout << s.Empty() << endl;
	
	while(!s.Empty())
		cout << s.Pop() <<" ";
	// s.Pop(); // pop when stack is empty, throws exception
	return 0;
}
