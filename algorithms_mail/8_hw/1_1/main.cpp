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

void dfs_topo (map<char, set<char>> &g, char v, map<char, bool> &used, vector<char> &ans) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to])
            dfs_topo (g, to, used, ans);
    }
    ans.push_back(v);
}

void topo_sort(map<char, set<char>> &g, vector<char> &ans) {
    int n = g.size();
    map<char, bool> used;

    for (auto v : g)
        used[v.first] = false;

    for (auto v : g)
        if (!used[v.first])
            dfs_topo (g, v.first, used, ans);
    reverse (ans.begin(), ans.end());
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<string> words;
    string s;
    for (int i = 0; i < m; i++) {
        cin >> s;
        words.push_back(s);
    }

    map<char, set<char>> g;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int k;
            int len = (int) min(words[i].size(), words[j].size());

            for (k = 0; k < len && words[i][k] == words[j][k]; k++);
//            printf("i, j, k, letters: %d %d - %d %c %c\n", i, j, k, words[i][k], words[j][k]);
            if (k < len) {
                g[words[i][k]].insert(words[j][k]);
            }
        }
    }

//    for (auto v : g) {
//        printf("%c: ", v.first);
//        for (auto u : v.second)
//            printf("%c ", u);
//        printf("\n");
//    }

    vector<char> ans;

    topo_sort(g, ans);

    for (int i = 0; i < ans.size(); i++) {
        printf("%c", ans[i]);
    }
    return 0;
}
