/*
    Given an int 'n', find all primes existing between 1 and 'n'

    Solution:
        We use a table of size 'n' denoting each number including 'n' and mark all of them as 
        primes initially. Then we start with 2, mark all its multiples as non-primes, then go to the next
        non marked number and check if it is prime by traversing through all sqrt(that number), again
        mark all its multiples as non-primes.
        Each time we are seiving numbers, in total n/2 + n/3 + n/5 ...n/p ~ n(1/2 + 1/3 .. 1/p)  ~ n*(loglogn)   

        Space Optimization: since half of the numbers are even so we can exclude them and use only n/2 space.
        Now each index i => 2*i + 1, to take it to the next level we can even remove the first 3 numbers 0, 1 and 2.
        That makes each index i => 2*i + 3
        TC: O(n*(loglogn))
        Sc: O(n), for saving the numbers 
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// finds all prime numbers between 1 and n
vector<int> findAllPrimes(int n) {
    // for storing the prime numbers
    vector<int> primes;
    // for tracking prime numbers, we will be excluding even numbers
    // so each index represents 2*i + 3 number
    // the range starts from 3
    vector<int> prime_candidates(floor(n / 2), true);

    for(int i = 0; i < prime_candidates.size(); i++) {
    	int candidate = 2 * i + 3;
    	// if the current is a prime
    	if(prime_candidates[i]) {
    		// mark all its multiples as non-prime
    		for(int j = i; j < prime_candidates.size(); j += candidate)
    			prime_candidates[j] = false;
    		// add the number to prime number list
    		primes.emplace_back(candidate);
    	}
    }
    return primes;
}

ostream& operator<<(ostream& out, vector<int> arr) {
    for(const auto& a: arr)
        cout << a << " ";
    cout << endl;
}

int main() {
    int n = 115;
    cout << findAllPrimes(n);
    return 0;
}
