#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

long long div_high(long long x, long long y) {
    return (x + y - 1) / y;
}

int main()
{
    long long n, a, b;
    scanf("%lld%lld%lld", &a, &b, &n);
    long long s = (long long) floor(sqrt(a) * sqrt(b) * sqrt(n));

    long long x, y, p, q;
    for (;;s++) {
        x = s / a;
        y = div_high(n, x);
        p = x * a;
        q = y * b;
        if (p <= s && q <= s) {
            printf("%lld", s);
            break;
        }
    }
}
