/*
    Given array of increasing size such that when placed acc. to their size they form a traingle.
    Find the min sum path value starting from the top to the bottom array.

    Solution:
        For finding the min path we need to know the sum of path values at each position in
        previous level. Then we add the path values for current level, do this till last level.
        When at last level, location with least value is min sum path.
        TC: O(n^2), there are 'n' arrays and ith level array has 'i' no. of elements and it takes O(i) for each level 'i'
        SC: O(n^2)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

// finds the min sum path value in a triangle
int minSumPathTriangleValue(vector<vector<int>>& triangle) {
	if(triangle.empty())
		return 0;
		
    // for storing the path sum values till current level
    vector<int> curr_level_sum;
    // for storing the previous level path sums
    // this vector stores only the immediate previous level values
    vector<int> previous_level_sum;

    // give the starting element, i.e pyramid top
    previous_level_sum.emplace_back(triangle.front().front());

    for(int i = 1; i < triangle.size(); i++) {
        // the only possible location accessible for the left most of current 
        // level is the first element of previous, same goes for the right most of current level
        curr_level_sum.emplace_back(previous_level_sum.front() + triangle[i].front());

        // from each previous location only two locations below it can be accessed
        for(int j = 1; j < triangle[i].size() - 1; j++) {
            // we add only the max sum for each location possible
            curr_level_sum.emplace_back(min(previous_level_sum[j - 1] + triangle[i][j], previous_level_sum[j] + triangle[i][j]));
        }

        curr_level_sum.emplace_back(previous_level_sum.back() + triangle[i].back());
        // make the current level sum as the previous level sum for the upcoming level
        previous_level_sum = move(curr_level_sum);
    }

    // find the min in the last level
    int min_value = numeric_limits<int>::max();
    for(const auto& a: previous_level_sum) {
    min_value = min( min_value, a);
    }
    	
    return min_value;
}

int main() {
    vector<vector<int>> triangle = {    {2},
                                       {4, 4},
                                      {8, 5, 6},
                                     {4, 2, 6, 2},
                                    {1, 5, 2, 3, 4}
                                };

    cout << minSumPathTriangleValue(triangle);
    return 0;
}
