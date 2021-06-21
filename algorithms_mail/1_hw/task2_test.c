#include <stdio.h>
#include <stdlib.h>

#define MAX_INT 4294967295

void exp_euc_alg(unsigned long long int a, unsigned long long int b, unsigned long long int *x, unsigned long long int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return;
  }
  unsigned long long int x1, y1;
  exp_euc_alg(b % a, a, &x1, &y1);
  *x = y1 - b / a * x1;
  *y = x1;
}

unsigned long long int by_mod(unsigned long long int x, unsigned long long int m) {
  x = x % m;
  return (x >= 0 ? x : x + m);
}

unsigned long long int find_inv(unsigned long long int p, unsigned long long int m) {
  unsigned long long int x, y;
  exp_euc_alg(p, m, &x, &y);
  return by_mod(x, m);
}

int main(void) {
  unsigned long long p, m, q;
  for (int i = 0; i < 10000; i++) {
    p = by_mod(rand() * rand() * rand() * rand(), MAX_INT);
    m = by_mod(rand() * rand() * rand() * rand(), MAX_INT);
    q = find_inv(p, m);
    printf("q: %lld \t p: %lld \t m: %lld\n", q, m, p);
  }
}
