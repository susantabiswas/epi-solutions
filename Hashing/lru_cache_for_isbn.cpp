/*
	Create lookup, insert and delete methods for ISBN of 10digits. 
	Use LRU scheme for caching.

	Solution:
		We make a 'n' sized cache, and a queue which contains the ISBN entries. Hash table uses reference to the
		ISBN entries in queue as value and ISBN as key. When an ISBN is looked up we bring the entry in queue to front. 
		Once the queue has 'n' elements, delete the tail ISBN.

		TC: Hash table Lookup: O(1), queue : O(1)  
		SC: O(n), n: cache size [n sized hash table and queue]
*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

template <size_t capacity>
class LRUCache{
	private:
	    // cache: key:isbn, value: pair<reference of isbn in queue list, price>
		unordered_map<int, pair<list<int>::iterator, int>> isbn_cache_;	
		list<int> lru_queue_;	// linked list implementation for queue for making middle elements as front in O(1)
	
		void MoveIsbnToFront(int isbn, 
				const unordered_map<int, pair<list<int>::iterator, int>> :: iterator it) {
				
				cout << "LRU Queue updated\n";
				
				// update the lru_queue and bring this isbn to front
				lru_queue_.erase(it->second.first);
				// add the isbn to front
				lru_queue_.emplace_front(isbn);
				// update the entry in cache
				it->second.first = lru_queue_.begin();
		}

	public:
		// for inserting isbn in cache
		void InsertISBN(int isbn, int price) {
			// search for the input isbn 
			auto it = isbn_cache_.find(isbn);

			// if the isbn is already present then just update the lru queue, we 
			if(it != isbn_cache_.end()) {
				// bring the isbn to front of lru queue
				MoveIsbnToFront(isbn, it);
			} else {
				// if the cache is full, then remove the least recently used isbn from queue and cache
				if(isbn_cache_.size() == capacity) {
					// remove the least recently used isbn from cache
					isbn_cache_.erase(lru_queue_.back());
					// remove from lru cache
					lru_queue_.pop_back();
					
					cout << "Old ISBN deleted\n";
				}
				cout << "ISBN added to cache\n";
				
				// add the new isbn
				lru_queue_.emplace_front(isbn);
				isbn_cache_[isbn] = {lru_queue_.begin(), price};
			}
		}

		// for deleting isbn from cache
		bool EraseISBN(int isbn) {
			// check for the isbn in cache
			auto it = isbn_cache_.find(isbn);

			// when the isbn is found
			if(it != isbn_cache_.end()) {
				lru_queue_.erase(it->second.first);
				isbn_cache_.erase(it);
				return true;
			}
			// when the isbn is not found
			return false;
		}

		// for doing isbn lookup
		bool LookupISBN(int isbn, int* price){
			// check if the isbn is there in cache 
			auto it = isbn_cache_.find(isbn);

			// if the isbn is there in cache
			if(it != isbn_cache_.end()) {
				*price = it->second.second;
				// move the isbn to front of lru queue
				MoveIsbnToFront(isbn, it);
				return true;
			}

			// when the isbn is not there in cache
			return false;
		}
};

int main() {
	LRUCache<2> cache;
	int* price = new int(0);
	
	cache.InsertISBN(1111123123, 100);
	cache.InsertISBN(1111111111, 200);
	cout << "Lookup: "<< cache.LookupISBN(1111111111, price) << endl;
	cout << "Price: " << *price << endl;
	cout << "Erased: " <<cache.EraseISBN(1111111111)<<endl;
	cache.InsertISBN(1111111111, 200);
	cache.InsertISBN(1111111111, 200);
	cache.InsertISBN(1111111112, 200);
	
	return 0;
}
