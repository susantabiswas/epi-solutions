/*
    Binary Search
*/
#include <iostream>
#include <vector>
using namespace std;

// Recursive binary search
// Returns the index if found else -1
int doBinarySearch(vector<int>& arr, int& value_to_search, int l, int h){
    if(l > h){
        return -1;
    }

    // find the middle index, ensuring no overflow
    int mid = l + (h - l) / 2;
    
    if(arr[mid] == value_to_search)
        return mid;
    else if(arr[mid] > value_to_search){
        return doBinarySearch(arr, value_to_search, l, mid-1);
    }
    else if(arr[mid] < value_to_search){
        return doBinarySearch(arr, value_to_search, mid+1, h);
    }
}

// Binary Search iteratively
int doBinarySearchIter(vector<int>& arr, int value_to_search, int l, int h){
    // for taking middle index
    int mid;

    while( l <= h){
        // find the middle index
        mid = l + (h - l) / 2;

        // check the left, right and middle conditions
        if(arr[mid] == value_to_search)
            return mid;
        else if(arr[mid] > value_to_search){
            h = mid - 1;
        }
        else if(arr[mid] < value_to_search){
            l = mid + 1;
        }
    }
    // when the element is not found
    return -1;
}

// driver function for doing binary search
int binarySearch(vector<int>& arr, int value_to_search){
    int l = 0;  // lower index
    int h = arr.size() - 1; // upper index

    //return doBinarySearch(arr, value_to_search, l, h);
    return doBinarySearchIter(arr, value_to_search, l, h);
}

int main(){
    vector<int> arr = {-23, -1, 0, 2, 5, 6, 123, 872, 9089};
    
    cout << binarySearch(arr, 6);
    return 0;
}