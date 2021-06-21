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

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
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

    vector<pair> edges = {{0, 0}, {0, n - 1}, {n - 1, 0}, {n - 1, n - 1}};

    int ans = 0;
    pair elem = sources[0];

    for (auto edge : edges) {
        ans = MAX(ans, distance(elem, edge));
    }

    printf("after edges: %d\n", ans);

    for (int i = 0; i < k; i++) {
        pair elem = sources[i];
        printf("elem: %d %d\n", elem.x, elem.y);

        for (auto edge : edges) {
            ans = MAX(ans, distance(elem, edge));
        }

        for (int j = 0; j < i; j++) {
            pair elem_2 = sources[j];
            printf("\telem_2: %d %d\n", elem_2.x, elem_2.y);

            int dist_between = distance(elem, elem_2);
            printf("\t\tdist: %d\n", dist_between);
            ans = MAX(ans, (dist_between + 1) / 2);
        }
    }

    printf("%d", ans);
    return 0;
}
