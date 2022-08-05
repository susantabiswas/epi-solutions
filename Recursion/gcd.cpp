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

// finds the GCD of two numbers
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

/*
    TC: O(logn), n = max(n, m)
    Worst case is when n and m are consecutive fibonacci terms.
    n = fib(N), m = fib(N-1)
    n = fib(N-1) + fib(N-2)
    n = m + k
    
    now n = n % m 
    n = k (since diff between n and m is k)
    after swapping
    so n = b(fib(N-1))
    m = k (fib(N-2))
    
    n = fib(N-1) + fib(N-2),
    so it will take N fibonacci steps, so complexity reduces to finding 
    complexity of finding Nth fibonacci num
    which is (golden ratio) ^ N
    
    (1.62) ^ N = n
    N = log(1.62 base) (n)
    N = log(n)
    
    where n = max of inputs 
*/
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


int main(){
    cout << gcd2(20, 0) << endl;
    return 0;
}
