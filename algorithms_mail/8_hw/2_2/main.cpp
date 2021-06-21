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

void is_acyclic (vector<vector<arrow>> const &g, int v, vector<color> &color, bool &ok) {
    if (!ok)
        return;

    color[v] = grey;

    for (auto u : g[v]) {
        if (color[u.to] == white) {
            is_acyclic(g, u.to, color, ok);
        }
        if (color[u.to] == grey) {
            ok = false;
        }
    }
    color[v] = black;
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

    // delete routs from finish (they are excess)
    g[finish].clear();

    vector<color> colors(n, white);
    bool is_acyc = true;

    is_acyclic(g, start, colors, is_acyc);
    if (!is_acyc) {
        printf("is acyc\n");
    } else {
        printf("is good\n");
    }
    return 0;
}
