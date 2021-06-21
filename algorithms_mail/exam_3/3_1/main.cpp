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

void dfs(vector<vector<int>> const &g, int node_index, vector<bool> &used)
{
    used[node_index] = true;
    for (auto i : g[node_index])
    {
        if (!used[i])
            dfs(g, i, used);
    }
}

bool is_euler(vector<vector<int>> const &g) {
    int odd_v = 0;
    int n = g.size();

    for (int v = 0; v < n; v++) {
        if (g[v].size() % 2 == 1) {
            odd_v++;
        }
    }
    if (odd_v > 2)
        return false;

    vector<bool> visited(n, false);
    dfs(g, 0, visited);

    for (int v = 0; v < n; v++) {
        if (!visited[v])
            return false;
    }

    return true;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d",&x, &y);
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
    }

    bool ans = is_euler(g);
    if (ans)
        printf("YES");
    else
        printf("NO");

    return 0;
}
