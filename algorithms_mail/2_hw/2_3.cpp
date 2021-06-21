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
  FILE *f = fopen("inp.txt", "r");
  size_t n;
  scanf("%zu", &n);
  vvll arr(n, vll(2));

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < 2; j++) {
      scanf("%lld", &arr[i][j]);
    }
  }

  sort(arr.begin(), arr.end(), [](vll a, vll b) {return a[1] < b[1];});

  // for (size_t i = 0; i < n; i++) {
  //   for (size_t j = 0; j < 2; j++) {
  //     printf("%lld ", arr[i][j]);
  //   }
  //   printf("\n");
  // }

  ll total_weight = 0;
  size_t count = 0, ind = 0;
  while(ind < n) {
    ll force = arr[ind][1];
    if (force < total_weight)
      ind++;
    else {
      total_weight += arr[ind][0];
      count++;
      ind++;
    }
  }
  printf("%zu", count);
}
