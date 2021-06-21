#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;

int main()
{
    long long k_by_2, radix;
    const long long mod = 1000000009;
    scanf("%lld%lld", &k_by_2, &radix);

    long long k = k_by_2 / 2;
    long long n = (k + 1) * radix + 1;
    vector<long long> now(n, 0);

    for (long long i = 1; i <= radix; i++) {
        now[i] = 1;
    }

    vector<long long> next(n, 0);
    for (long long iter = 2; iter <= k; iter++) {
        for (long long pos = iter; pos <= iter * radix; pos++) {
            for (long long delta = 1; delta <= radix; delta++) {
                if (pos - delta >= 0) {
                    next[pos] += now[pos - delta];
                    next[pos] %= mod;
                }
            }
        }
        now = next;

        next.clear();
        next.assign(n, 0);
    }

    long long sum = 0;
    for (long long i = 1; i <= radix * k; i++) {
//        printf("%lld ", now[i]);
        sum += (now[i] * now[i]) % mod;
        sum %= mod;
    }
    printf("\n%lld\n", sum);
    return 0;
}