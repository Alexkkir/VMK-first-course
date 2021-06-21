
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
using std::vector;

#define SIZE 1000000000

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;


int main() {
  int n;
  scanf("%d", &n);
  vll a(n);
  vll b(n);
  vll CountDigit(10);

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  int count = 0, tmp, dig, x;
  for (int d_i = 0; d_i < 35; d_i++) {
    for (int j = 0; j < 10; j++) {
      CountDigit[j] = 0;
    }
    for (int j = 0; j < n; j++) {
      x = a[j];
      for (int i = 0; i < d_i; i++) x /= 10;
      dig = x % 10;
      CountDigit[dig]++;
    }
    count = 0;
    for (int j = 0; j < 10; j++) {
      tmp = CountDigit[j];
      CountDigit[j] = count;
      count += tmp;
    }
    for (int j = 0; j < n; j++) {
      x = a[j];
      for (int i = 0; i < d_i; i++) x /= 10;
      dig = x % 10;
      b[CountDigit[dig]] = a[j];
      CountDigit[dig]++;
    }
    a = b;
  }

  // b = a;
  for (int i = 0; i < n; i++) {
    printf("%10d\n", b[i]);
  }
}
