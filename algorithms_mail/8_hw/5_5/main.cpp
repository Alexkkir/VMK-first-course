#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::unordered_set;

#define  MAXN 2000

int get_bit(int x, int k) {
    return (x >> (31 - k)) & 1;
}

void transitive_closure(vector<unordered_set<int>> const &g, vector<unordered_set<int>> &ans) {
    int n = g.size();
    copy(g.begin(), g.end(), back_inserter(ans));

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
//                ans[i][j] = ans[i][j] | (ans[i][k] & ans[k][j]);
                if (ans[i].find(k) != ans[i].end() && ans[k].find(j) != ans[k].end()) {
                    ans[i].insert(j);
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int g[n];
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while(scanf("%c", &c) && !(c == '0' || c == '1'));

            if (c - '0' == 1) {
                g[i] |= (1 << j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int k = g[i];
            while(k > 0) {

            }
            printf("%d", g[i]);
        }
        printf("\n");
    }

    vector<unordered_set<int>> ans(n);

    transitive_closure(g, ans);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", ans[i].find(j) != ans[i].end() ? 1 : 0);
        }
        printf("\n");
    }

    return 0;
}
