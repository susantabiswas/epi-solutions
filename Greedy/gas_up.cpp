/*
	There are 'n' cities lying on circumference of a circular road. Each of the cities has a gas 
	station. Now total gas combined from all the stations is equal to the amount
	required for covering the circular road once. The car can run 1km per litre.(Changed to make solution simpler) 
	
	There is one city from which if we start and then refill the tank at each station, then
	we will be able to reach that station again while moving in the circular path covering other 
	cities. Find that station. 
	Assume there always exists such a city.
	
	Input: vector of gas amount for each city, 
		   vector of gas required for reaching the next city
			
	Output: the starting city 

	Solution:
		1. If there exists any such city then the total sum of all (gas[i] - cost[i]) >= 0. If this is not the
		   case then no such city can exist.
		2. Once we start traversing, if at pos 'i' remaining gas becomes < 0, then that means that all city from 
			current start city till 'i' cannot be the starting point. This is because we have reached till 'ith' city only
			because everytime we had surplus gas, now if we remove the surplus from the current start then the
			remaining city don't even stand a chance. So the next city to pick is 'i+1'
	
	NOTE: Below is a generalized algo where it is not necessary that such a city exists.
	TC: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

// returns the index of starting city if coverage is possible else returns -1
int isPossibleCityCoverage(vector<int>& gas, vector<int>& cost){
	// first find the total sum 
	int total = 0;
	int remaining = 0;
	int start = 0;
	const int n = gas.size();
	
	// we assume that coverage is possible, so we can start traversing the cities
	for(int i = 0; i < gas.size(); i++){
		total += gas[i] - cost[i];
		// current fuel
		remaining += gas[i] - cost[i];
		
		// if there is no remaining gas, change the start point to i+1
		if(remaining < 0){
			start = (i + 1) % n;
			// make the surplus fuel 0 again, since journey starts from here
			remaining = 0;
		}
	}
	// coverage is only possible if the total is +ve
	return total < 0 ? -1:start;
}

int main(){
	vector<int> gas = {6, 3, 7};
	vector<int> cost = {4, 6, 3};
	
	cout << isPossibleCityCoverage(gas, cost);
	return 0;
}
