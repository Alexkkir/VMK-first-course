#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <map>

using std::map;
using std::set;
using std::unordered_map;
using std::unordered_multiset;
using std::multiset;
using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

#define ABS(x) x > 0 ? x : -x
#define MAX(a, b) a > b ? a : b

#define INF 1000000009
#define MAX_UNS 4294967295


int main() {
    int n;
    cin >> n;

    map<int, set<string>> MAP;
    set<string> ans;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        MAP[s.size()].insert(s);
    }

    for (auto it = MAP.begin(); it != MAP.end(); it++) {
        int len = it->first;
        for (auto target : it->second) {
            for (int i = 1; i < target.size(); i++) {
                if (MAP[i].find(target.substr(0, i)) != MAP[i].end() &&
                MAP[len - i].find(target.substr(i)) != MAP[len - i].end()) {
                    ans.insert(target);
                    break;
                }
            }
        }
    }

    for (auto q : ans) {
        cout << q << endl;
    }
}
