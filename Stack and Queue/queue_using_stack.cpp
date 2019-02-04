/*
	Implement queue using stack.
	Input: 
	Output: queue class 

	Solution:
		The idea is to use two stacks s1 and s2. For pushing the elements, we insert it in s1. For removing elements, we need to
		remove the first entered element, which we can get by popping the stack elements from s1 to s2. The top element
		is the first element, which we then remove. Again for enqueue we use s1 and for dequeue if s2 is not empty
		then it can be done in O(1). For dequeue we are moving 'n' elements at a time and after that for removing the
		'n' elements it will take one pop from stack only which is O(1).

		TC: enqueue: O(1)
			dequeue: O(n), for n dequeue operations
		 
*/

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <sstream>
using namespace std;

template<typename T>
class Queue {
	private:
		stack<T> enqueue_;
		stack<T> dequeue_;

	public:
		// for pushing element
		void Enqueue(T data) {
			enqueue_.emplace(data);
		}

		// for popping element
		T Dequeue() {
			// first check if dequeue stack is empty or not
			if(dequeue_.empty()) {
				T data;
				// fill it with enqueue stack elements
				while(!enqueue_.empty()) {
					data = enqueue_.top();
					enqueue_.pop();
					dequeue_.emplace(data);
				}
			}
			
			if(dequeue_.empty()) 
				throw length_error("Queue is empty");
			
			T popped_data = dequeue_.top();
			dequeue_.pop();
			return popped_data;
		}

		// checks if queue is empty or not
		bool Empty() {
			return enqueue_.empty() && dequeue_.empty();
		}
};

int main() {
	Queue<int> queue;

	for(size_t i = 0; i < 6; i++)
		queue.Enqueue(i);
	
	while(!queue.Empty()) {
		cout << queue.Dequeue() << " ";
	}cout << queue.Dequeue() << " ";
	return 0;
}
 
