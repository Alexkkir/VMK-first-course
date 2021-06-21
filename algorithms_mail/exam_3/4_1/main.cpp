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

#define  MAXN 801


void floyd_warshall(int **g, int n, int **ans) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = g[i][j];
        }
    }



    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (ans[i][k] && ans[k][j] && i != j)
                    if (ans[i][k] + ans[k][j] < ans[i][j] || ans[i][j] == 0)
                        ans[i][j] = ans[i][k] + ans[k][j];
            }
        }

//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                printf("%d ", ans[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
    }
}

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);

    int **g = (int **) calloc (MAXN, sizeof(int*));
    for (int i = 0; i < MAXN; i++) {
        g[i] = (int *) calloc(MAXN, sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        g[x][y] = w;
    }

    int **ans = (int **) malloc (MAXN * sizeof(int*));
    for (int i = 0; i < MAXN; i++) {
        ans[i] = (int *) malloc(MAXN * sizeof(int));
    }

    // algorithm
    floyd_warshall(g, n, ans);

    // check

    int **ans_2 = (int **) malloc (MAXN * sizeof(int*));
    for (int i = 0; i < MAXN; i++) {
        ans_2[i] = (int *) malloc(MAXN * sizeof(int));
    }
    bool neg = false;

    floyd_warshall(ans, n, ans_2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j] != ans_2[i][j]) {
                neg = true;
                printf("IMPOSSIBLE");
                return 0;
            }
        }
    }
    
//    bool neg = false;
//    for (int i = 0; i < n; i++) {
//        if (ans[i][i] < 0) {
//            neg = true;
//            printf("IMPOSSIBLE");
//            return 0;
//        }
//    }

//     print
    for (int j = 0; j < n; j++) {
        int d = ans[s][j];
        if (d == 0 && j != s)
            printf("UNREACHABLE ");
        else {
            printf("%d ", d);
        }
    }

    return 0;
}