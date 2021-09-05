#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::pair;

static int first, second;

struct xy {
    double x, y;
};

double dist(xy a, xy b) {
    return sqrt(
            (a.x - b.x) * (a.x - b.x) +
            (a.y - b.y) * (a.y - b.y)
    );
}

int cmp_ii(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) {
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

pair<double, pair<int, int>> fun(vector<pair<xy, int>> &dots, int left, int right) {
    if (left == right - 1) {
        return {dist(dots[left].first, dots[right].first), {dots[left].second, dots[right].second}};
    }

    auto ans1 =  fun(dots, left, (left + right) / 2);
    double d1 = ans1.first; pair<int, int> best1 = ans1.second;
    
    auto ans2 = fun(dots, (left + right) / 2, right);
    double d2 = ans2.first; pair<int, int> best2 = ans2.second;
    
    double mind;
    pair<int, int> best;
    if (d1 < d2) {
        mind = d1;
        best = best1;
    } else {
        mind = d2;
        best = best2;
    }

    xy cent = dots[(left + right) / 2].first;
    vector<pair<xy, int>> check;

    for (int i = (left + right) / 2; i >= 0 && abs(cent.x - dots[i].first.x) < mind; i--) {
        check.push_back(dots[i]);
    }
    for (int i = (left + right) / 2 + 1; i < dots.size() && abs(cent.x - dots[i].first.x) < mind; i++) {
        check.push_back(dots[i]);
    }

    sort(check.begin(), check.end(), [](pair<xy, int> a, pair<xy, int> b){return a.first.y < b.first.y;});

    for (int i = 0; i < check.size(); i++) {
        for (int j = i - 3; j <= i + 3; i++) {
            if (j >= 0 && j < check.size() && j != i) {
                if (dist(check[i].first, check[j].first) < mind) {
                    mind = dist(check[i].first, check[j].first);
                    best = {check[i].second, check[j].second};
                } else if (dist(check[i].first, check[j].first) < mind) {
                    if (cmp_ii({i, j}, best)) {
                        best = {check[i].second, check[j].second};
                    }
                }
            }
        }
    }

    for (int i = 0; i < check.size(); i++) {
        for (int j = i - 1; j >= i - 3 && j >= 0; j--) {
            if (dist(check[i].first, check[j].first) < mind) {
                mind = dist(check[i].first, check[j].first);
                best = {check[i].second, check[j].second};
            } else if (dist(check[i].first, check[j].first) < mind) {
                if (cmp_ii({i, j}, best)) {
                    best = {check[i].second, check[j].second};
                }
            }
        }
        for (int j = i + 1; j <= i + 3 && j < check.size(); j++) {
            if (dist(check[i].first, check[j].first) < mind) {
                mind = dist(check[i].first, check[j].first);
                best = {check[i].second, check[j].second};
            } else if (dist(check[i].first, check[j].first) < mind) {
                if (cmp_ii({i, j}, best)) {
                    best = {check[i].second, check[j].second};
                }
            }
        }
    }

//    for (int i = 0; i < check.size(); i++) {
//        for (int j = 0; j < i; j++) {
//            if (dist(check[i].first, check[j].first) < mind) {
//                mind = dist(check[i].first, check[j].first);
//                best = {check[i].second, check[j].second};
//            } else if (dist(check[i].first, check[j].first) < mind) {
//                if (cmp_ii({i, j}, best)) {
//                    best = {check[i].second, check[j].second};
//                }
//            }
//        }
//    }

    return {mind, best};
}

int main() {
    int n;
    std::cin >> n;

    vector<pair<xy, int>> dots(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        dots[i] = {{x, y}, i + 1};
    }

    sort(dots.begin(), dots.end(), [](pair<xy, int> d1, pair<xy, int> d2){return d1.first.x > d2.first.x;});
    
    auto ans = fun(dots, 0, n);
    int p1 = std::min(ans.second.first, ans.second.second);
    int p2 = std::max(ans.second.first, ans.second.second);

    printf("%.10lf %d %d", ans.first, p1, p2);
    return 0;
}
