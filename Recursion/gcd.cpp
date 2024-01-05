/*
    Problem:
        Find the GCD( Greatest Common Diviser) of two numbers a and b.
        TC: O(max(a, b)) or O(n), where n=no. of bits 
        Since every time the function is called one of the numbers is atleast halved,
        that means the function s called till a number doesn't becomes zero, so 
        at max it can last for max(a, b) of bits

        b >= a / 2, then after swap will make b at most half of its previous value
        b < a / 2, then after swap will make a at most half of its previous value, since b is less than a / 2
    Input:
        Real numbers a and b

    Output:
        GCD of 'a' and 'b'
*/

#include<iostream>
#include<vector>
using namespace std;

// EUCLIDEAN DIVISION METHOD: finds the GCD of two numbers
/*
    TC: O(logn), n = max(n, m)
    Worst case is when n and m are consecutive fibonacci terms.
    n = fib(N), m = fib(N-1)
    n = fib(N-1) + fib(N-2)
    n = m + k
    
    now n = n % m 
    New values: gcd(n % m, m) => (k, m) => (F(N-2), F(N-1))
    n = k (since diff between n and m is k)

    after swapping
    so n = m which is (fib(N-1))
    m = k which is (fib(N-2))
    
    So we will now solve for the greater value F(N-1), so effectively we
    took only one fibonaaci step. This means, it will take N fib steps to reach the
    terminal value 1.
    Nth fib number = N^(golden ratio) ~ N ^ 1.62
    
    (1.62) ^ N = n
    N = log(1.62 base) (n)
    N = log(n)
    
    where n = max of inputs 
*/
int gcd(const int a, const int b){
    // if the bigger number is zero, that means the 'b' 
    // can divide 'a'
    if(a == 0)
        return b;
    // We check which is the bigger number frst, then
    // the recurse with the remainder and diviser
    if(a > b)
        return gcd(a % b, b);
    else
        return gcd(b % a, a);
}

int gcd2(int n, int m) {
    if (m == 0) 
        return n;
    if (n < m) swap(n, m);
    while (m > 0) {
        n = n % m;
        swap(n, m);
    }
    return n;
}

/*
    Subtraction Method

    TC: O(a + b)

    Worst case is when the diff is decreased by only 1 in each call. This means we are progressing
    by making the greater number smaller by just 1.
    This can continue till we reach the base case of 1 in worst case.
    So O(a + b)
*/
int gcd3(int a, int b) {
    if(a == b)
        return b;
    if(a > b)
        return gcd3(a - b, b);
    else
        return gcd3(b - a, a);
}

int main(){
    cout << gcd2(20, 0) << endl;
    return 0;
}
