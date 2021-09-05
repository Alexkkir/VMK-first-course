#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::string;
using std::endl;

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define MIN_3(a, b, c) MIN(a, MIN(b, c))
#define INF 1000000000


int main() {
    int n;
    cin >> n;
    map<int, set<string>> a;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int len = s.size();
        a[len].insert(s);
    }

    set<string> ans;

    for (auto it = a.rbegin(); it != a.rend(); it++) {
        int len = it->first;
        for (const auto& target : it->second) {
            for (int i = 1; i <= len - 1; i++) {
                if (a[i].find(target.substr(0, i)) != a[i].end() &&
                    a[len - i].find(target.substr(i)) != a[len - i].end()) {
                    ans.insert(target);
                }
            }
        }
    }

    for (auto elem : ans) {
        cout << elem << endl;
    }
    return 0;
}
