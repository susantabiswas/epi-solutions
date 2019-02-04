/*
	Different sorting algorithms.
*/
#include <iostream>
#include <vector>
#include <random>
#include <utility>
using namespace std;


// bubble sort
// TC: O(n^2)
// This is modified version of classical bubble sort where the best case is O(n)
vector<int> bubbleSort(vector<int> arr) {
	bool sorted = true;
	
	for(int i = 0; i < arr.size() - 1; i++) {
		for(int j = 0; j < arr.size() - i - 1; j++) {
			if(arr[j] > arr[j+1]) {
				swap(arr[j], arr[j+1]);
				sorted = false;	// array is unsorted
			}
		}
		
		// when array is already sorted
		if(sorted)
			return arr;	
	}
	return arr;
}

// selection sort 
// TC: O(n^2)
vector<int> selectionSort(vector<int> arr) {
	int min_el;
	
	for(int i = 0; i < arr.size() - 1; i++) {
		// assume ith element to be the smallest
		min_el = i;
		for(int j  = i+1; j < arr.size(); j++) {
			if(arr[j] < arr[min_el])
				min_el = j;
		}
		// swap the first el and min element index 
		swap(arr[i], arr[min_el]);
	}
	return arr;
}

// insertion sort
// TC: O(n^2), best case: O(n)
vector<int> insertionSort(vector<int> arr) {
	int j = 0;
	
	for(int i = 1; i < arr.size(); i++) {
		j = i;
		while(j > 0 && arr[j-1] > arr[j]) {
			swap(arr[j-1], arr[j]);
			--j;
		}
	}
	
	return arr;
}

// for partitioning the array such that pivot is placed at its correct position
int partitionArray(vector<int>& arr, int pivot_idx, int l, int h) {
	// pivot index
	int pivot_value = arr[pivot_idx];
	// swap the pivot element with last element for making the partition process easier
	swap(arr[h], arr[pivot_idx]);
	// tracks position where next smaller element can be placed
	int small = l;
	
	for(int i = l; i < h; i++) {
		// swap only when the current element is smaller than pivot
		if(arr[i] < pivot_value) {
			swap(arr[i], arr[small]);
			++small;
		}
	}
	
	// swap the pivot with its correct position
	swap(arr[h], arr[small]);
	return small;
}


// helper function for quick sort, basically this does the real work
vector<int> quickSortHelper(vector<int>& arr, int l, int h, default_random_engine gen) {
	if(l <= h) {
		// generate a random pivot index
		int pivot_idx = uniform_int_distribution<int>{l, h}(gen);
		// partition about the pivot
		int partition_idx = partitionArray(arr, pivot_idx, l, h);
		
		// do for left and right subarrays
		quickSortHelper(arr, l, partition_idx-1, gen);
		quickSortHelper(arr, partition_idx+1, h, gen);
	}
	return arr;
}

// quick sort
// TC: O(n^2), avg case: O(nlogn)
vector<int> quickSort(vector<int> arr) {
	int l = 0, h = arr.size() - 1;
	// for generating random numbers
	default_random_engine gen((random_device())());
	return quickSortHelper(arr, l, h, gen);
}

// for merging the subarrays of merge sort
void mergeArrays(vector<int> arr, int l1, int h1, int l2, int h2) {
	const int N = h1 - l1 + 1;	// left subarray size
	const int M = h2 - l2 + 1; // right subarray size
	// temp array for storing sorted elements
	vector<int> temp(M + N);
	int a1 = l1;	// for left subarray
	int a2 = l2;	// for right subarray
	int curr = 0;	// for temp array
	
	// place the smallest element out of two accordingly
	while(a1 <= h1 && a2 <= h2) {
		temp[curr++] = arr[a1] < arr[a2] ? arr[a1++] : arr[a2++];
	}
	// put elements from left subarray if right has finished
	while(a1 <= h1)
		temp[curr++] = arr[a1++];
	// put elements from right subarray if left subarray has finished
	while(a2 <= h2)
		temp[curr++] = arr[a2++];
	
	// copy sorted elements
	for(int i = l1; i <= h2; i++)
		arr[i] = temp[i-l1];
}

// helper function for merge sort
vector<int> mergeSortHelper(vector<int>& arr, int l, int h) {
	if(l <= h) {
		int mid = l + (h - l) / 2 ;
		mergeSortHelper(arr, l, mid-1);
		mergeSortHelper(arr, mid+1, h);

		mergeArrays(arr, l, mid-1, mid+1, h);
	} 
	return arr;
}

// merge sort
// TC: O(nlogn)
// SC: O(n)
vector<int> mergeSort(vector<int> arr) {
	int l = 0, h = arr.size()-1;
	return mergeSortHelper(arr, l, h);
}

ostream& operator<<(ostream& out, vector<int> arr) {
	for(const auto& d: arr)
		cout << d << " ";
	cout << endl;
}

int main() {
	vector<int> arr = {0, -2, -3, 6, 3, 2, 17, 2, 7, -4, 9};
	
	cout << "Original:\n" << arr;
	cout << "Bubble Sort:\n" << bubbleSort(arr);
	cout << "Selection Sort:\n" << selectionSort(arr);
	cout << "Insertion Sort:\n" << insertionSort(arr);
	cout << "Quick Sort:\n" << quickSort(arr);
	return 0;
}