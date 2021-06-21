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

#define MAXN 10000

struct edge {
    int vert;
    int weight;
};

struct comp {
    bool operator()(const edge a, const edge b) {
        return a.vert < b.vert;
    }
};

void MST(vector<vector<int>> const &g, vector<vector<int>> &ans) {
    int n = g.size();
    const int INF = 1000000000; // значение "бесконечность"

    vector<bool> used (n);
    vector<int> min_e (n, INF), sel_e (n, -1);
    min_e[0] = 0;
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
//        if (min_e[v] == INF) {
//            cout << "No MST!";
//            exit(0);
//        }

        used[v] = true;
        if (sel_e[v] != -1)
            ans.push_back({v, sel_e[v], min_e[v]});

        for (int to=0; to<n; ++to)
            if (g[v][to] != 0 && g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }
}


int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &g[i][j]);
            g[i][j] *= -1;
        }
    }

    vector<vector<int>> ans;
    MST(g, ans);

    int sum = 0;
    for (auto elem : ans) {
        sum+= elem[2];
    }
    printf("%d", -sum);

    return 0;
}
