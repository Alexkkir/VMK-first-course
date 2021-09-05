#include <iostream>
#include <string>
#include <vector>
#include <map>
//#include <set>
//using std::set;
using std::map;
using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::pair;
using ull = unsigned long long;

const ull P = 29;
const char ZERO = 'a';

#if 0
int main() {
    string s;
    cin >> s;
    int n = s.length();

    vector<ull> ptab (n);
    ptab[0] = 1;
    for (int i = 1; i < n; i++) {
        ptab[i] = ptab[i - 1] * P;
    }

    vector<ull> htab (n + 1);
    htab[0] = 0;
    for (int i = 1; i <= n; i++) {
        htab[i] = htab[i - 1] + (s[i - 1] - ZERO) * ptab[i - 1];
    }

    vector<ull> m(n);
    map<ull, int> counter;
    for (int len = n - 1; len >= 1; len--) {
        counter.clear();
        counter[m[0]] = 1;
        ull k = 1;
        for (int i = n - len; i >= 0; i--) {
            m[i] = (htab[i + len] - htab[i]) * k;
            k *= P;
            if (counter.find(m[i]) == counter.end()) {
                counter[m[i]] = 1;
            } else {
                cout << s.substr(i, len);
                return 0;
            }
        }
    }
    return 0;
}
#endif
string s;
int n;
vector<ull> ptab, htab;

int fun(int len) {
    if (len == 0) {
        return n;
    } else if (len == n) {
        return 1;
    }
    map<ull, map<int, int>> counter;
    vector<ull> m(n);
    ull k = 1;

    for (int i = n - len; i >= 0; i--) {
        m[i] = (htab[i + len] - htab[i]) * k;
        k *= P;
        if (counter.find(m[i]) == counter.end()) {
            counter[m[i]] = {{i, 1}};
        } else {
//            counter[m[i]]++;
//            max = counter[m[i]];
            auto elem = counter[m[i]];
            for (auto pos : elem) {
                if (s.substr(i, len) == s.substr(pos.first, len)) {
                    elem[pos.first]++;
                } else {
                    elem[i] = 1;
                }
            }
            counter[m[i]] = elem;
        }
    }
//    for (auto q : counter) {
//        printf("%d ", q);
//    }
//    printf("\n");
    int max = 1;
    for (auto hashes : counter)
        for (auto pos : hashes.second) {
            max = std::max(max, pos.second);
        }
    return max;
}

int bs(int minimal) {
    int left = 0, right = n - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        int val = fun(mid);

        if (val >= minimal) {
            left = left + (right - left) / 2;
        } else if (val < minimal) {
            right = right - (right - left) / 2;
        }
    }

    if (right - left == 1 && fun(right) == minimal)
        return right;

    return left;
}

string find_substr(int len) {
    if (len == 0) {
        return "";
    } else if (len == n) {
        return s;
    }
    map<ull, map<int, int>> counter;
    vector<ull> m(n);
    ull k = 1;

    for (int i = n - len; i >= 0; i--) {
        m[i] = (htab[i + len] - htab[i]) * k;
        k *= P;
        if (counter.find(m[i]) == counter.end()) {
            counter[m[i]] = {{i, 1}};
        } else {
//            counter[m[i]]++;
//            max = counter[m[i]];
            auto elem = counter[m[i]];
            for (auto pos : elem) {
                if (s.substr(i, len) == s.substr(pos.first, len)) {
                    return s.substr(pos.first, len);
                } else {
                    elem[i] = 1;
                }
            }
            counter[m[i]] = elem;
        }
    }
    return "";
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

//    for (int i = 0; i < n; i++) {
//        printf("%d %d\n", i, fun(i));
//    }

    int ans = bs(2);

    cout << find_substr(ans);
}