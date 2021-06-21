#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
using std::vector;

struct arrow {
    int comp;
    bool is_path = false;
};

int start, finish;

vector<int> companies;
vector<bool> companies_satisfied;
vector<vector<arrow>> g;
vector<bool> visited;
int n_of_unsatisfied = 0;
int n_paths_to_finish = 0;

void print_g() {
    int ind = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            if (g[i][j].is_path == false) {
                printf("-; ");
            }
            else {
                printf("%d; ", g[i][j].comp);
            }
        }
        printf("\n");
    }
}

void dsf(int v, int path_length) {
    if (v == finish) {
        n_paths_to_finish++;
        for (int id = 1; id < companies.size(); id++) {
            if (companies[id] == 0 && companies_satisfied[id] == true) {
                companies_satisfied[id] = false;
                n_of_unsatisfied++;
            }
        }
        return;
    } else {
        visited[v] = true;
        for (int u = 0; u < g.size(); u++) {
            if (g[u][v].is_path == true && visited[u] == false) {
                companies[g[v][u].comp]++;
                dsf(u, path_length + 1);
                companies[g[v][u].comp]--;
            }
        }
        visited[v] = false;
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

    print_g();

    companies.assign(c, 0);
    companies_satisfied.assign(c, true);
    visited.assign(n, false);

    dsf(start, 0);

    printf("n_paths_to_finish: %d\n", n_paths_to_finish);

    printf("%d\n", n_of_unsatisfied);
    if (n_of_unsatisfied != 0) {
        for (int id = 0; id < companies_satisfied.size(); id++) {
            if (companies_satisfied[id] == false) {
                printf("%d ", id);
            }
        }
    }
    return 0;
}