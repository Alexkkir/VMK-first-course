#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::map;
using std::set;

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define MIN_3(a, b, c) MIN(a, MIN(b, c))
#define INF 1000000000

struct pair{
    int x, y;
};

void print_v(vector<vector<int>> const &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            printf("%d ", v[i][j] != INF ? v[i][j] : 0);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<vector<int>> board(n + 2, vector<int>(m + 2, 0));

    queue<pair> q;

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        x++;
        y++;

        board[x][y] = 1;
        q.push({x, y});
    }

    int rest = n * m - k;
    int max_dist = 0;

//    print_v(board);

    while(!q.empty()) {
        pair p = q.front();
        q.pop();

//        printf("x, y %d %d\n", p.x, p.y);

//        vector<pair> neighbours = {{p.x - 1, p.y}, {p.x + 1, p.y},
//                                   {p.x, p.y - 1}, {p.x, p.y + 1}};
        vector<pair> neighbours;
        neighbours.clear();

        if (p.x - 1 != 0) {
            neighbours.push_back({p.x - 1, p.y});
        }
        if (p.x + 1 != n + 1) {
            neighbours.push_back({p.x + 1, p.y});
        }
        if (p.y - 1 != 0) {
            neighbours.push_back({p.x, p.y - 1});
        }
        if (p.y + 1 != m + 1) {
            neighbours.push_back({p.x, p.y + 1});
        }

        for (auto v : neighbours) {
//            printf("\tv.x, v.y %d %d\n", v.x, v.y);
            if (board[v.x][v.y] == 0) {
                board[v.x][v.y] = board[p.x][p.y] + 1;
                max_dist = MAX(max_dist, board[v.x][v.y]);
                q.push({v.x, v.y});
            }
        }

//        print_v(board);
    }

    printf("%d", max_dist - 1);
}