/*
    Problem:
        Given pivot index, partition the array such that all
        elements smaller are on the left and greater are on the left and
        equal are in the middle.

    Input: int array
    Output: arranged array
    
    Solution:

        Solution 1:
            We maintain three indices which contains three ranges:
            1. smaller than pivot: [0 : smaller - 1]
    		2. equal to pivot: [smaller : equal - 1]
        	3. Unclassified: [equal: larger - 1]
        	4. larger than pivot: [larger : SIZE_N - 1]

            Now let the three indices be small, equal and large. Initially small and equal are at 0.
            We use equal index for traversal. Whenever an element is encountered which is smaller than 
            current, we swap it with element at smaller index. Smaller indicates position where
            current smaller will be written and equal represents position where current equal will be 
            written, and larger represents position where larger will be written/
            TC: O(n)
            SC: O(1)

        Solution 2:
            Use two passes:
            1. forward pass: we traverse the array and put all the smaller elements on the left
            2. backward pass: we start from back and put all larger on the back

            TC: O(n)
            SC: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// partitions the flag colors
vector<int> partitionArraySolution1(int pivot_idx, vector<int> arr) {
    // pivot value
    int pivot = arr[pivot_idx];
    /*
        1. smaller than pivot: [0 : smaller - 1]
        2. equal to pivot: [smaller : equal - 1]
        3. Unclassified: [equal: larger - 1]
        4. larger than pivot: [larger : SIZE_N - 1]
    */
    int smaller = 0, larger = arr.size(), equal = 0;

    while(equal < larger) {
        if(arr[equal] < pivot) {
            swap(arr[equal++], arr[smaller++]);
        }   
        else if(arr[equal] == pivot) {
            ++equal;
        } 
        else if(arr[equal] > pivot) {
            swap(arr[equal], arr[--larger]);
        }
    }
    
    return arr;
}

// solution 2
vector<int> partitionArraySolution2(int pivot_idx, vector<int> arr) {
    // pivot value 
    int pivot = arr[pivot_idx];

    // forawrd pass
    int smaller = 0;
    for(int i = 0; i < arr.size(); i++) {
        // if the current element is smaller then swap
        if(arr[i] < pivot) {
            swap(arr[smaller++], arr[i]);
        }
    }

    // backward pass 
    int larger = arr.size() - 1;
    for(int j = arr.size() - 1; j >= 0 && arr[j] >= pivot; j--) {
        // if the current is larger than pivot
        if(arr[j] > pivot) 
            swap(arr[j], arr[larger--]);
    }

    return arr;
}

ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr) 
        cout << a << " ";
    cout << endl;
}

int main(){
    vector<int> arr = {1, 23, 4, 67, 2, 898, 2, 9, 56, 4, 67, 23, 1, 98};
    cout << "Originally:\n" << arr << endl;
    int pivot_idx = 3;
    cout << partitionArraySolution1(pivot_idx, arr);
    cout << endl << partitionArraySolution2(pivot_idx, arr);
    return 0;
}
