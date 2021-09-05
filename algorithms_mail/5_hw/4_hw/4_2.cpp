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

typedef struct {
    double x;
    double y;
    int pos;
} point;

void print(point *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f %f\n", a[i].x, a[i].y);
    }
    printf("\n");
}

int comp_x(const void *a, const void *b) {
    return (*(point*) a).x < (*(point*) b).x;
}

int comp_y(const void *a, const void *b) {
    return (*(point*) a).y < (*(point*) b).y;
}

void sort_x(point *a, int left, int right) {
    qsort(a + left, right - left, sizeof(point), comp_x);
}

void sort_y(point *a, int left, int right) {
    qsort(a + left, right - left, sizeof(point), comp_y);
}


double dist(point *a, int i, int j) {
    double x = a[i].x - a[j].x;
    double y = a[i].y - a[j].y;
    double ans = sqrt(x * x + y * y);
    //printf("ans l r: %lf %d %d\n", ans, i, j);
    return ans;
}

double fun(point *a, point *aux, int left, int right) {
    if (left >= right) {
           return e;
    }
    if (left == right - 1) {
        return dist(a, left, right);
    }

    int mid = (left + right) / 2;
    double d1, d2, d;
    d1 = fun(a, aux, left, mid);
    d2 = fun(a, aux, mid + 1, right);
    d = MIN(d1, d2);

    printf("1");

    int l, r;
    for (l = mid; l >= 0 && a[mid].x - a[l].x < d; l--);
    for (r = mid; r <= n - 1 && a[r].x - a[mid].x < d; r++);
    l++; r--;

    printf("2");

    for (int i = l; i <= r; i++) {
        aux[i] = a[i];
    }
    printf("3");

    sort_y(aux, l, r);

    //printf("4");

    for (int i = l; i <= r; i++) {
        for (int j = MAX(i - 10, 0); j < i; j++) {
            int t1 = (int) aux[j].pos + 1;
            int t2 = (int) aux[i].pos + 1;
            int p1 = MIN(t1, t2);
            int p2 = MAX(t1, t2);


            //printf("%d %d %lf\n", p1, p2, dist(a, i, j));
            if (dist(aux, i, j) < d) {
                d = dist(aux, i, j);
                best_1 = p1;
                best_2 = p2;
            }
            else if (dist(aux, i, j) == d) {
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

    point *a, *aux;
    a = (point*) malloc (n * sizeof(point));
    aux = (point*) malloc (n * sizeof(point));

    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &a[i].x, &a[i].y);
        a[i].pos = i;
    }

    best_1 = n + 1, best_2 = n + 1;
    e = dist(a, 0, 1);
    sort_x(a, 0, n - 1);

    double ans = fun(a, aux, 0, n - 1);
    printf("%lf %d %d", ans, best_1, best_2);
}
