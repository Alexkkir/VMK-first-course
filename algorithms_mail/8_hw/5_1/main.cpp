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

#define  MAXN 2000

void floyd_warshall(vector<vector<int>> const &g, vector<vector<int>> &ans) {
    int n = g.size();
    ans = g;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = ans[i][j] | (ans[i][k] & ans[k][j]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> g(n, vector<int>(n));
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while(scanf("%c", &c) && !(c == '0' || c == '1'));

            g[i][j]  = (int) (c - '0');
        }
    }

    vector<vector<int>> ans(n, vector<int>(n));

    floyd_warshall(g, ans);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
