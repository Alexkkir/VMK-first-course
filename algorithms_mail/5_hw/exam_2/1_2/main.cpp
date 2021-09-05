#include <iostream>

using namespace std;

#define max(a, b) (a > b) ? a : b

int main()
{
    long long n, a, b;
    scanf("%lld%lld%lld", &a, &b, &n);

    long long x_count = 0, y_count = 0, amount = 0, x_len = 0, y_len = 0;

    while (amount < n) {
        if (x_len + a < y_len + b) {
            x_len += a;
            x_count++;
            amount += y_count;
        }
        else {
            y_len += b;
            y_count++;
            amount += x_count;
        }
    }
    printf("%lld", max(x_count * a, y_count * b));
    return 0;
}
