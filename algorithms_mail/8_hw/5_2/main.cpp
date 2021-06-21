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


void floyd_warshall(const int g[MAXN][MAXN], int n, int ans[MAXN][MAXN]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = g[i][j];
        }
    }

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

    int g[MAXN][MAXN];
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while(scanf("%c", &c) && !(c == '0' || c == '1'));

            g[i][j]  = (int) (c - '0');
        }
    }

    int ans[MAXN][MAXN];

    floyd_warshall(g, n, ans);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
