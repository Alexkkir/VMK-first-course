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
const int INF = 1000000000;

void dijkstra(vector<vector<pair<int,int>>> const &g, int s, vector<int> &p, vector<int> &d) {
    int n = g.size();
    p.clear();
    d.clear();
    p = vector<int>(n);
    d = vector<int>(n, INF);
    set<pair<int,int>> q;

    d[s] = 0;
    q.insert({d[s], s});

    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (size_t j = 0; j < g[v].size(); j++) {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert ({d[to], to});
            }
        }
    }
}

void dijkstra_fires(vector<vector<pair<int,int>>> const &g, vector<int> starts, vector<int> &p, vector<int> &d,
                    vector<int> const &path, vector<int> const &dist) {
    int n = g.size();
    p.clear();
    d.clear();
    p = vector<int>(n);
    d = vector<int>(n, INF);
    set<pair<int,int>> q;

    for (auto s : starts) {
        d[s] = 0;
        q.insert({d[s], s});
    }

    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (size_t j = 0; j < g[v].size(); j++) {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert ({d[to], to});
            }
        }
    }
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<int> fires(k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &fires[i]);
        fires[i]--;
    }

    vector<vector<pair<int,int>>> g(n);
    int a, b, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        a--;
        b--;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    int s, f;
    scanf("%d%d", &s, &f);
    s--;
    f--;

    vector<int> parent, dist;
    dijkstra(g, s, parent, dist);

    vector<int> path;
    int v = f;
    int time = dist[f];

    if (time == INF) {
        printf("-1");
        return 0;
    }

    while (v != s) {
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(s);
    reverse(path.begin(), path.end());

    // обход в ширину одновременно из всех вершин
    vector<int> dist_f;
    dijkstra_fires(g, fires, parent, dist_f, path, dist);

    bool ok = true;
    for (auto e : path) {
//        printf("%d %d %d\n", e + 1, dist_f[e], dist[e]);
        if (dist_f[e] <= dist[e]) {
            ok = false;
            break;
        }
    }

    printf("%d", ok ? time : -1);
}