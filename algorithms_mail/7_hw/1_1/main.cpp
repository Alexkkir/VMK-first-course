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
    // Initially i stored in massive not probabilities,
    // but numbers that meant quantity of cases,
    // when exact number may appear as sum of cube's values.
    // But that didn't work.
    long long k, x;
    scanf("%lld%lld", &k, &x);
    
    long long n = (k + 1) * 6 + 1;
    vector<double> now(n, 0);

    now[1] = 1.0/6;
    now[2] = 1.0/6;
    now[3] = 1.0/6;
    now[4] = 1.0/6;
    now[5] = 1.0/6;
    now[6] = 1.0/6;

    vector<double> next(n, 0);
    for (long long iter = 2; iter <= k; iter++) {
        for (long long pos = iter; pos <= iter * 6; pos++) {
            for (long long delta = 1; delta <= 6; delta++) {
                if (pos - delta >= 0) {
                    next[pos] += now[pos - delta];
                }
            }
            next[pos] /= 6;
        }
        now = next;

        next.clear();
        next.assign(n, 0);
    }

    printf("%.9lf",now[x]);
    return 0;
}
