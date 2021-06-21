#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::unordered_set;
using std::unordered_map;
using ull=unsigned long long;

#define MAX(a, b) a > b ? a : b
const int p = 29;

struct freq_t {
    int x = 0;
};

int main() {
    string s;
    cin >> s;

    int n = s.size();
//    vector<int> weights(n, 0);

    unordered_map<string, freq_t> freq;

    int ans = 0;
    for (int length = 1; length <= n; length++) {
        int best = 0, curr;
        for (int pos = 0; pos < n + 1 - length; pos++) {
            curr = ++freq[s.substr(pos, length)].x;
            best = MAX(best, curr);
        }
        ans = MAX(ans, best * length);

        freq.clear();
    }

    printf("%d", ans);
    return 0;
}
