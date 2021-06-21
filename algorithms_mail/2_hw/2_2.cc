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

int comp(long long *x, long long *y) {
  return (int) (x[1] < y[1]);
}

int main() {
  FILE *f = fopen("inp.txt", "r");
  size_t n;
  fscanf(f, "%zu", &n);

  long long **a;
  a = (long long**) calloc(n, sizeof(long long*));
  for (int i = 0; i < n; i++) {
    a[i] = (long long*) calloc(2, sizeof(long long));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; i++) {
      fscanf(f, "%lld", &a[i][j]);
    }
  }


  sort(a, n, sizeof(long long*), [](long long *x, long long *y) {return x[1] < y[1];});

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; i++) {
      printf("%lld", a[i][j]);
    }
  }
}
