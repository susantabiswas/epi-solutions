/*
    Problem:
        Dutch Flag problem: Given an array consisiting of three colours, arrange the 
        elements such that the elements with same color come together.

    Input: int array
    Output: arranged array
    
    Solution:
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
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef enum {RED, WHITE, BLUE} Colors;

// partitions the flag colors
vector<Colors> partitionDutchFlagColors(int pivot_idx, vector<Colors> arr) {
    // Pivot value
    Colors pivot = arr[pivot_idx];
    /*
        1. smaller than pivot: [0 : smaller - 1]
        2. equal to pivot: [smaller : equal - 1]
        3. Unclassified: [equal: larger - 1]
        4. larger than pivot: [larger : SIZE_N - 1]
    */
    int smaller = 0, equal = 0, larger = arr.size();

    while(equal < larger) {
        // when the current color is lesser than pivot
        if(arr[equal] < pivot) {
        	// equal is also incremented because whatever be swapped with current
        	// equal index will be equal to pivot for sure, since that element has already been passed
        	// by equal index 
            swap(arr[smaller++], arr[equal++]);
        }   
        else if(arr[equal] == pivot) {
            ++equal;
        }   // when the color is larger than pivot
        else {
        	// equal is not incremented because we are not sure what element will come
        	// after swapping at equal index, but larger is decremented since it is sure it will get
        	// a larger element
            swap(arr[equal], arr[--larger]);
        }
    }
    return arr;
}

ostream& operator<<(ostream& out, vector<Colors> arr) {
    for(const auto& a: arr) 
        cout << a << " ";
    cout << endl;
}

int main(){
    vector<Colors> arr = {RED, WHITE, RED, BLUE, WHITE, RED, WHITE, WHITE, BLUE, BLUE, RED};
    cout << "Originally:\n" << arr << endl;
    int pivot_idx = 1;
    cout << partitionDutchFlagColors(pivot_idx, arr);
    return 0;
}
