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

int main() {
  int n; scanf("%d", &n);
  int a[n];
  int inv = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    for (int j = 0; j < i; j++) {
      if (a[j] > a[i]) inv++;
    }
  }
  printf("%d", inv);
}
