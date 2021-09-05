#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
//#include <set>
//using std::set;
using std::unordered_map;
using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::pair;
using ull = unsigned long long;

const ull P = 29;
const char ZERO = 'a';

string s;
int n;
vector<ull> ptab, htab;

#define STRCMP 0

int fun(int len) {
    if (len == 0) {
        return n;
    } else if (len == n) {
        return 1;
    }
#if STRCMP
    unordered_map<ull, unordered_map<int, int>> counter;
#else
    unordered_map<ull, int> counter;
#endif
    vector<ull> m(n);
    ull k = 1;

    for (int i = n - len; i >= 0; i--) {
        m[i] = (htab[i + len] - htab[i]) * k;
        k *= P;
        if (counter.find(m[i]) == counter.end()) {
#if STRCMP
            counter[m[i]] = {{i, 1}};
#else
            counter[m[i]] = 1;
#endif
        } else {
#if STRCMP
            auto elem = counter[m[i]];
            for (auto pos : elem) {
                if (s.substr(i, len) == s.substr(pos.first, len)) {
                    elem[pos.first]++;
                } else {
                    elem[i] = 1;
                }
            }
            counter[m[i]] = elem;
#else
            counter[m[i]]++;
#endif
        }
    }
//    for (auto q : counter) {
//        printf("%d ", q);
//    }
//    printf("\n");
    int max = 1;
#if STRCMP
    for (auto hashes : counter)
        for (auto pos : hashes.second) {
            max = std::max(max, pos.second);
        }
#else
    for (auto hashes : counter)
        max = std::max(max, hashes.second);
#endif
    return max;
}

int main() {
    cin >> s;
    n = s.length();

    ptab.assign(n, 0);
    ptab[0] = 1;
    for (int i = 1; i < n; i++) {
        ptab[i] = ptab[i - 1] * P;
    }

    htab.assign(n + 1, 0);
    htab[0] = 0;
    for (int i = 1; i <= n; i++) {
        htab[i] = htab[i - 1] + (s[i - 1] - ZERO) * ptab[i - 1];
    }

    int ans = 0;
    for (int len = 1; len <= n; len++) {
        int val = fun(len) * len;
        ans = std::max(ans, val);
    }
    printf("%d", ans);
}