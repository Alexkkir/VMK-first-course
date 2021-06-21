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
    vector<int> uns_comps_before;

    arrow(int to_, int who_, int n) {
        to = to_;
        who = who_;
        uns_comps_before.assign(n, 0);
    }
};

enum color {
    white,
    grey,
    black
};

void bsf(vector<vector<arrow>> const &g, int start, int finish, vector<int> &ans) {
    int n = g.size();
    queue<int> q;
    vector<color> color(n, white);
    int paths_to = 0;

    q.push(start);
    color[start] = grey;

    while (!q.empty()) {
        int u = q.front();
        printf("u: %d\n", u + 1);
        q.pop();

        for (auto v : g[u]) {
            if (color[v.to] != black) {
                printf("\tv: %d\n", v.to + 1);
                q.push(v.to);
                if (v.to == finish) {
                    paths_to++;
                }
                color[v.to] = grey;
            }
        }
        color[u] = black;
    }

    printf("paths to: %d\n", paths_to);
}

int main() {
    int n, m, c_n;
    scanf("%d%d%d", &n, &m, &c_n);

    vector<vector<arrow>> g(n);

    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;

        g[a].push_back(arrow(b, c, n));
        g[b].push_back(arrow(a, c, n));
    }

    int start, finish;
    scanf("%d%d", &start, &finish);
    start--;
    finish--;

    vector<int> ans;
    bsf(g, start, finish, ans);
    return 0;
}
