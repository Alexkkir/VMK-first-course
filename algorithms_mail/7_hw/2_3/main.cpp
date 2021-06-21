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

int fun(string s, vector<vector<int>> &d, int left, int right) {
    if (left > right) {
        return 0;
    } else if (left == right) {
        return d[left][right] = 1;
    } else if (d[left][right] != -1) {
        return d[left][right];
    } else {
        int ans_1, ans_2, ans_3, ans_4, medium;

        medium = fun(s, d, left + 1, right - 1);

        ans_1 = (s[left] == s[right]) ? (medium + 1) : 0;

        ans_2 = fun(s, d, left + 1, right - 1);

        ans_3 = fun(s, d, left + 1, right) -
                medium;

        ans_4 = fun(s, d, left, right - 1) -
                medium;

        return d[left][right] = ans_1 + ans_2 + ans_3 + ans_4;
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
    string s;
    cin >> s;

    int n = s.size();
    vector<vector<int>> d(n, vector<int> (n, -1));

    int ans = fun(s, d, 0, n - 1);

//    print_2v(d);

    printf("%d", ans);
    return 0;
}