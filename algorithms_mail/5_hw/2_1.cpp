#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

typedef struct {
    long long x, y, z;
} point;

bool cmp_x (point a, point b) {
    return a.x < b.x;
}

bool cmp_y (point a, point b) {
    return a.y < b.y;
}

bool cmp_z (point a, point b) {
    return a.z < b.z;
}

void print_arr(point *arr, size_t n) {
    printf("Array:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%lld %lld %lld\n", arr[i].x, arr[i].y, arr[i].z);
    }
    printf("\n");
}

int main() {
    size_t n;
    scanf("%zu", &n);

    point *arr = (point*) malloc(n * sizeof(point));

    /*
    6
    1 1 0
    1 2 0
    1 3 0
    -1 -2 0
    -1 -1 0
    -1 -3 0
    */

    for (size_t i = 0; i < n; i++) {
        long long x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        x *= 2;
        y *= 2;
        z *= 2;
        arr[i].x = x;
        arr[i].y = y;
        arr[i].z = z;
    }

    //cout << "==========" << endl;

    long long x_max, x_min,
        y_max, y_min,
        z_max, z_min;

    sort(arr, arr + n, cmp_z);
    z_min = arr[0].z;
    z_max = arr[n - 1].z;

    stable_sort(arr, arr + n, cmp_y);
    y_min = arr[0].y;
    y_max = arr[n - 1].y;

    stable_sort(arr, arr + n, cmp_x);
    x_min = arr[0].x;
    x_max = arr[n - 1].x;

    //print_arr(arr, n);
    point cent = {(x_min + x_max) / 2, (y_min + y_max) / 2, (z_min + z_max) / 2};

    //printf("Center: %lld %lld %lld\n", cent.x, cent.y, cent.z);

    bool good = true;
    size_t sim;
    for (size_t i = 0; i < n / 2 + 1; i++) {
        sim = (n - 1) - i;
        if ( !( (arr[i].x + arr[sim].x) / 2 == cent.x &&
                (arr[i].y + arr[sim].y) / 2 == cent.y &&
                (arr[i].z + arr[sim].z) / 2 == cent.z)) {
            good = false;
            break;
        }
    }

    if (good == true) {
        printf("Yes");
    }
    else {
        printf("No");
    }
}
