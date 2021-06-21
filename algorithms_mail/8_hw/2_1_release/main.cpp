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

struct arrow {
    int comp;
    bool is = false;
    bool used = false;
};

int start, finish;

vector<int> comps;
vector<bool> comps_sat;
vector<vector<arrow>> g;
int uns = 0;
int paths_to = 0;

void print_g() {
    int ind = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            if (g[i][j].is == false) {
                printf("- -; ");
            }
            else {
                printf("%d %d; ", g[i][j].comp, g[i][j].used);
            }
        }
        printf("\n");
    }
}

void dsf(int v, int length) {
    if (uns == g.size() && length > g.size() + 5) {
        return;
    }
    if (v == finish) {

        paths_to++;
        for (int id = 1; id < comps.size(); id++) {
            if (comps[id] == 0 && comps_sat[id] == true) {
                comps_sat[id] = false;
                uns++;
            }
        }
        return;
    } else {
        for (int u = 0; u < g.size(); u++) {
            if (g[u][v].is == true && g[v][u].used == false) {
                g[v][u].used = true;
                g[u][v].used = true;
                comps[g[v][u].comp]++;

                dsf(u, length + 1);

                g[v][u].used = false;
                g[u][v].used = false;
                comps[g[v][u].comp]--;
            }
        }
    }
}

int main() {
    int n, m, c;
    scanf("%d%d%d", &n, &m, &c);
    c++;

    g.assign(n, vector<arrow>(n));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;
        g[a][b] = {c, true};
        g[b][a] = {c, true};
    }

    scanf("%d%d", &start, &finish);
    start--;
    finish--;

//    print_g();

    comps.assign(c, 0);
    comps_sat.assign(c, true);

    dsf(start, 0);

//    printf("paths_to: %d\n", paths_to);

    printf("%d\n", uns);
    if (uns != 0) {
        for (int id = 0; id < comps_sat.size(); id++) {
            if (comps_sat[id] == false) {
                printf("%d ", id);
            }
        }
    }
    return 0;
}
