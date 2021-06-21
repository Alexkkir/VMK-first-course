#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;

#define MAXN 37

int fun(char *s, int d[MAXN][MAXN], int left, int right) {
    if (left == right) {
        return d[left][right] = 1;
    } else if (left > right) {
        return 0;
    } else {
        // decomposition by last symbol
        int ans_1 = 0, ans_2, ans;

        ans_1 = fun(s, d, left, right - 1);

        // calc ans_2
        ans_2 = 0;
        for (int tmp = left; tmp <= right; tmp++) {
            if (s[tmp] == s[right]) {
                ans_2 += fun(s, d, tmp + 1, right - 1) + 1;
            }
        }

        ans = ans_1 + ans_2;
        return d[left][right] = ans;
    }

}

void print_2v(vector<vector<int>> const &d) {
    for (int i = 0; i < d.size(); i++) {
        for (int j = 0; j < d[i].size(); j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char s[MAXN];
    scanf("%s", s);

    int n = strlen(s);
    int d[MAXN][MAXN];

    int ans = fun(s, d, 0, n - 1);

//    print_2v(d);

    printf("%d", ans);
    return 0;
}
