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
using ull=unsigned long long;

struct arrow {
    bool is = false;

    int who = -1;
    ull worst = 0;
};

void print_g(vector<vector<arrow>> &g, int comp) {
    int ind = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {

            for (int k = 1; k <= comp; k++) {
                if (g[i][j].is == false) {
                    printf("-");
                } else {
                    printf("%llu", (g[i][j].worst & (1 << k)) >> k);
                }
            }
            printf(" ");
        }
        printf("\n");
    }
}

void floyd_warshall (vector<vector<arrow>> &g) {
    int n = g.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j].is) {
                    g[i][j].worst = g[i][j].worst &
                                    (
                                            (g[i][k].worst) |
                                            (g[k][j].worst)
                                    );
                } else {
                    g[i][j].is = g[i][j].is | (g[i][k].is & g[k][j].is);
                    if (g[i][j].is == true) {
                        g[i][j].worst = (
                                (g[i][k].worst) |
                                (g[k][j].worst)
                        );
                    }
                }

            }
        }

//        print_g(g, 2);
//        printf("\n");
    }
}

int main() {
    int n, m, c_n;
    scanf("%d%d%d", &n, &m, &c_n);
    c_n;

    vector<vector<arrow>> g;
    g.assign(n, vector<arrow>(n));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;
        ull c_1 = 1 << c;
        g[a][b] = {true, c, c_1};
        g[b][a] = {true, c, c_1};
    }

    int start, finish;
    scanf("%d%d", &start, &finish);
    start--;
    finish--;

//    print_g(g, 2);
//    printf("\n");

    floyd_warshall(g);

    int total = 0;
    for (int i = 1; i <= c_n; i++) {
        if ((g[start][finish].worst & (1 << i)) == 0) {
            total++;
            printf("%d ", i);
        }
    }
    printf("\n%d", total);
    return 0;
}
