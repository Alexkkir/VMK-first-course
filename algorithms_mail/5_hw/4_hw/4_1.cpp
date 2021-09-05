#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define MIN_INT -2147483648
#define MAX_INT 2147483647


#define MIN(a, b) (a < b) ? a : b
#define MAX(a, b) (a > b) ? a : b

using namespace std;
using std::vector;

int n;
double e;
int best_1, best_2;

void print(vector<vector<double>> a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f %f\n", a[i][0], a[i][1]);
    }
    printf("\n");
}

void sort_x(vector<vector<double>> &a, int left, int right) {
    sort(a.begin() + left, a.begin() + left + right + 1, [](vector<double> x, vector<double> y){return x[0] < y[0];} );
}

void sort_y(vector<vector<double>> &a, int left, int right) {
    sort(a.begin() + left, a.begin() + left + right + 1, [](vector<double> x, vector<double> y){return x[1] < y[1];} );
}

double dist(vector<vector<double>> &a, int i, int j) {
    double x = a[i][0] - a[j][0];
    double y = a[i][1] - a[j][1];
    double ans = sqrt(x * x + y * y);
    //printf("ans l r: %lf %d %d\n", ans, i, j);
    return ans;
}

double fun(vector<vector<double>> &a, int left, int right) {
    if (left >= right) {
           return e;
    }
    if (left == right - 1) {
        return dist(a, left, right);
    }

    int mid = (left + right) / 2;
    double d1, d2, d;
    d1 = fun(a, left, mid);
    d2 = fun(a, mid + 1, right);
    d = MIN(d1, d2);

    int l, r;
    for (l = mid; l >= 0 && a[mid][0] - a[l][0] < d; l--);
    for (r = mid; r <= n - 1 && a[r][0] - a[mid][0] < d; r++);
    l++; r--;

    for (int i = l; i <= r; i++) {
        for (int j = l; j <= r; j++) {
            if (j == i) continue;
            int t1 = (int) a[j][2] + 1;
            int t2 = (int) a[i][2] + 1;
            int p1 = MIN(t1, t2);
            int p2 = MAX(t1, t2);

            //printf("%d %d %lf\n", p1, p2, dist(a, i, j));
            if (dist(a, i, j) < d) {
                d = dist(a, i, j);
                best_1 = p1;
                best_2 = p2;
            }
            else if (dist(a, i, j) == d) {
                if (p1 < best_1) {
                    best_1 = p1;
                    best_2 = p2;
                }
                else if (p1 == best_1 && p2 < best_2) {
                    best_1 = p1;
                    best_2 = p2;
                }
            }
        }
    }
    return d;
}

int main() {
    scanf("%d", &n);

    vector<vector<double>> a(n, vector<double>(3));

    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &a[i][0], &a[i][1]);
        a[i][2] = i;
    }
    best_1 = n + 1, best_2 = n + 1;
    e = dist(a, 0, 1);
    sort_x(a, 0, n - 1);

    double ans = fun(a, 0, n - 1);
    printf("%lf %d %d", ans, best_1, best_2);
}
