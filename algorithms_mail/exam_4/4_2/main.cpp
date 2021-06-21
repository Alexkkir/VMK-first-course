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

int distance(pair a, pair b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<pair> sources;
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        sources.push_back({x, y});
    }

    int max_dist_ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int min_dist = INF;
            for (auto elem : sources) {
                pair v = {i, j};
//                printf("v: %d %d\n"
//                       "elem: %d %d\n"
//                       "dist: %d\n"
//                       "\n", i, j, elem.x, elem.y, distance(v, elem));
                min_dist = MIN(min_dist, distance(v, elem));
            }
            max_dist_ans = MAX(max_dist_ans, min_dist);
        }
    }

    printf("%d", max_dist_ans);

    return 0;
}
