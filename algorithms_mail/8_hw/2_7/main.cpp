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

struct arrow {
    int to;
    int who;
};

enum color {
    white,
    grey,
    black
};


void dsf (vector<vector<arrow>> const &g, int v, vector<bool> &visited, int without) {
//    printf("%d ", v);
    visited[v] = true;
    for (auto u : g[v]) {
        if (u.who != without && visited[u.to] == false) {
            dsf(g, u.to, visited, without);
        }
    }
}

int main() {
    // preparation
    int n, m, c_n;
    scanf("%d%d%d", &n, &m, &c_n);

    vector<vector<arrow>> g(n);

    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }


    int start, finish;
    scanf("%d%d", &start, &finish);
    start--;
    finish--;

    vector<bool> satisfied(c_n + 1, true);
    vector<bool> visited;
    for (int without = 1; without <= c_n; without++) {
        visited.assign(n, false);
//        printf("without %d\n", without);
        dsf(g, start, visited, without);
//        printf("\n");
        if (visited[finish]) {
            satisfied[without] = false;
        }
    }

    int count = 0;
    for (int i = 1; i <= c_n; i++) {
        if (satisfied[i] == false) {
            count++;
        }
    }
    printf("\n%d", count);

    for (int i = 1; i <= c_n; i++) {
        if (satisfied[i] == false) {
            printf("%d ", i);
        }
    }
    return 0;
}