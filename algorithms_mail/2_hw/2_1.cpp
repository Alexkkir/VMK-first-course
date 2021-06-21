#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
// #include <utility>

// #include <string_view>
using namespace std;
using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

#define max(a, b) (a > b) ? a : b

int main() {
  // FILE *f = fopen("inp.txt", "r");
  size_t n; scanf("%zu", &n);
  vvll arr(n, vll(2));

  for (size_t i = 0; i < n; i++) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    arr[i][0] = y; arr[i][1] = x;
  }

  sort(arr.begin(), arr.end(), [](vll a, vll b) {return a[1] < b[1];});
  stable_sort(arr.begin(), arr.end(), [](vll a, vll b) {return a[0] > b[0];});

  ll sum_weight = 0, hight = 1, delta = 0;
  for (size_t ind = 1; ind < n; ind++) {
    bool ok = true;
    for (size_t i = 0; i < ind; i++) {
      arr[i][0] -= arr[ind][1];
      if (arr[i][0] < -delta)
        ok = false;
        delta += arr[ind][1];
    }
    if (ok == true) {
      hight++;
    }
  }

  printf("%d", hight);

  // printf("\n===\n");
  // for (size_t i = 0; i < n; i++) {
  //   for (size_t j = 0; j < 2; j++) {
  //     printf("%d ", arr[i][j]);
  //   }
  //   printf("\n");
  // }

}
