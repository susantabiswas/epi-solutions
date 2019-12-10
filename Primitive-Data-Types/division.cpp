/*
    Divide x / y using '/' operator.
*/
int divide(int x, int y) {
    long long divisor = static_cast<long long>(y);
    long long dividend = static_cast<long long>(x);
    long long quotient = 0;

    // decide the sign
    bool negative = (x < 0) ^ (y < 0);
    divisor = abs(divisor), dividend = abs(dividend);

    // We start with the largest permissible multiple for the divisor
    // such that the divisor is still smaller than dividend,
    // then we add that bit to the quotient. The dividend is updated 
    // with dividend = dividend - divisor*multiple
    // Then we again find the next largest multiple that when multiplied with divisor
    // gives a value closer to dividend. Continue doing this till we get 0
    const int N_BITS = sizeof(int) * 8;
    for(int i = N_BITS - 1; i >= 0; i--) {
        // 2^i * divisor <= dividend
        if((divisor << i) <= dividend) {
            dividend -= divisor << i;  // dividend = dividend - divisor*2^i
            quotient |= 1LL << i;
        }
    }
    // add the sign if required
    quotient = negative ? -1 * quotient: quotient;

    // check for overflow
    if(quotient > numeric_limits<int>::max())
        quotient = numeric_limits<int>::max();
    return static_cast<int>(quotient); 
  }
