/*
	Implement a circular queue using an array.

	Input: 
	Output: queue class  

	Solution:
		We use two index trackers front and back, initially both are 0. When we enqueue then we make rear = (rear+1) mod capacity.
		This way it always stays inside the array. For dequeue we make front = (front+1). We keep track whether the array has become full or not also. 
		If it has become full, we first rotate the vector such that front is positioned at index 0 and rear stays at the back of vector, after
		that we resize by a constant factor. The vacant places gets appended after rear tracker.

		TC: enqueue: O(n), for 'n' operations of enqueue and amortized is O(1)
			dequeue: O(1)
		 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

template<typename T>
class Queue {
	private:
		vector<T> q_;
		int front_ = 0, rear_ = 0, num_elements_ = 0;
		const int RESIZE_FACTOR_ = 2;
	public:
		//constructor
		explicit Queue(int n) : q_(n){}

		// for pushing element
		void Enqueue(T data) {
			// if the vector is full, rotate and then resize
			if(num_elements_ == q_.size()) {
				// first rotate the array, otherwise if rear might overwrite data
				// current rear position or front becomes index 0
				rotate(q_.begin(), q_.begin() + rear_, q_.end());
				//change rear index
				rear_ = q_.size();
				//resize the array
				q_.resize(RESIZE_FACTOR_ * q_.size());
			}
			q_[rear_] = data;
			++num_elements_;
			// increment rear
			rear_ = (rear_ + 1) % q_.size();
		}

		// for popping element
		T Dequeue() {
			// check if the queue is empty or not
			if(num_elements_ == 0)
				throw length_error("Queue is empty");
			
			int popped_el = q_[front_];
			front_ = (front_ + 1) % q_.size();
			--num_elements_;
			
			return popped_el;	
		}

		// checks if queue is empty or not
		bool Empty() {
			return num_elements_ ? false : true;
		}

};

int main() {
	Queue<int> queue(5);
 
	for(size_t i = 0; i < 6; i++)
		queue.Enqueue(i);
	
	while(!queue.Empty()) {
		cout << queue.Dequeue() << " ";
	} 
	
	return 0;
}
 
