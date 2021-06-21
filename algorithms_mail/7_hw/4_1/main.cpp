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

#define MIN(a, b) ((a < b) ? a : b)
#define MIN_3(a, b, c) MIN(a, MIN(b, c))
#define INF 1000000000

void print_v(vector<vector<int>> const &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            printf("%d ", v[i][j] != INF ? v[i][j] : 0);
        }
        printf("\n");
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> field(n + 2, vector<int>(m + 2)), dinamo(n + 2, vector<int>(m + 2, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    dinamo[0].assign(m + 2, INF);
    dinamo[n + 1].assign(m + 2, INF);

    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            dinamo[i][j] = MIN_3(dinamo[i - 1][j - 1],
                                 dinamo[i    ][j - 1],
                                 dinamo[i + 1][j - 1]) + field[i][j];
        }
    }

//    print_v(field);
//    printf("\n");
//    print_v(dinamo);
//    printf("\n");

    int min_cost = INF;
    int end_city;
    for (int i = 1; i <= n; i++) {
        if (dinamo[i][m] < min_cost) {
            min_cost = dinamo[i][m];
            end_city = i;
        }
    }

    vector<int> path;
    path.push_back(end_city);
    for (int j = m - 1; j >= 1; j--) {
        int cost = INF;
        int next_city;

        for (int i = path.back() - 1; i <= path.back() + 1; i++) {
            if (dinamo[i][j] < cost) {
                cost = dinamo[i][j];
                next_city = i;
            }
        }

        path.push_back(next_city);
    }

    reverse(path.begin(), path.end());
    for (auto elem : path) {
        printf("%d ", elem);
    }
    printf("\n");
    printf("%d", min_cost);
    return 0;
}
