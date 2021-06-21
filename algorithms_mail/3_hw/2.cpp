#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

#define MAX_INT 2147483647

int i_min_el = 0;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vvll a(m, vll(n));
  int min_el = MAX_INT;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[j][i]);
      if (a[j][i] < min_el) {
        min_el = a[j][i];
        i_min_el = i;
      }
    }
  }

  sort(a.begin(), a.end(), [](vll x, vll y){return x[i_min_el] < y[i_min_el]; });

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //         printf("%d ", a[j][i]);
  //       }
  //       printf("\n");
  //     }
  // }

  vvll inds(n, vll(2));
  for (int i = 0; i < n; i++) {
    inds[i][0] = i;
    inds[i][1] = a[0][i];
  }

  sort(inds.begin(), inds.end(), [](vll x, vll y){return x[1] < y[1]; });
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", a[j][inds[i][0]]);
    }
    printf("\n");
  }
}
