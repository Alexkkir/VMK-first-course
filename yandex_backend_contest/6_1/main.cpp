#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

using std::unordered_map;
using std::unordered_multiset;
using std::multiset;
using std::set;

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

#define ABS(x) x > 0 ? x : -x
#define MAX(a, b) a > b ? a : b

#define INF 1000000009
#define MAX_UNS 4294967295
#define _10_9_ 1000000000

struct rectangle {
    long long x1, y1, x2, y2;
    
    long long square () {
        return (x2 - x1) * (y2 - y1);
    }
    
    long long has (long long x, long long y) {
        return x1 <= x && x <  x2 && y1 <= y && y < y2;
    }
};

int main() {
    long long n;
    scanf("%lld", &n);
    vector<rectangle> rects;
    set<long long> x_ticks, y_ticks;

//    x_ticks.insert(-_10_9_);
//    x_ticks.insert(_10_9_);
//    y_ticks.insert(-_10_9_);
//    y_ticks.insert(_10_9_);

    for (long long i = 0; i < n; i++) {
        long long x1, y1, x2, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        rects.push_back({x1, y1, x2, y2});
        x_ticks.insert(x1);
        x_ticks.insert(x2);
        y_ticks.insert(y1);
        y_ticks.insert(y2);
    }

    vector<long long> count(n, 0);

//    x_ticks.erase(prev(x_ticks.end()));
//    y_ticks.erase(prev(y_ticks.end()--));

    for (auto x_it = x_ticks.begin(); x_it != prev(x_ticks.end()); x_it++) {
        for (auto y_it = y_ticks.begin(); y_it != prev(y_ticks.end()); y_it++) {
            for (long long elem_i = n - 1; elem_i >= 0; elem_i--) {
                rectangle elem = rects[elem_i];
                if (elem.has(*x_it, *y_it)) {
                    auto x_it_copy = next(x_it);
                    auto y_it_copy = next(y_it);

                    count[elem_i] += (*x_it_copy - *x_it) * (*y_it_copy - *y_it);
                    break;
                }
            }
        }
    }

    for (auto q : count) {
        printf("%lld\n", q);
    }

    return 0;
}
