#include <stdio.h>
#include <stdlib.h>

void exp_euc_alg(long long int a, long long int b, long long int *x, long long int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return;
  }
  long long int x1, y1;
  exp_euc_alg(b % a, a, &x1, &y1);
  *x = y1 - b / a * x1;
  *y = x1;
}


long long int by_mod(long long int x, long long int m) {
  x = x % m;
  return (x >= 0 ? x : x + m);
}

long long int find_inv(long long int p, long long int m) {
  unsigned long long int x, y;
  exp_euc_alg(p, m, &x, &y);
  x = by_mod(x, m);
  return x;
}

int main(void) {
  long long int p, m;
  scanf("%lld%lld", &p, &m);
  p = by_mod(p, m);
  printf("%lld", find_inv(p, m));
}
