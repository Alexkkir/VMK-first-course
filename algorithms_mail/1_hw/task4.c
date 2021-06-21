#include <stdio.h>
#include <stdlib.h>

unsigned long long fact(unsigned long long n) {
  unsigned long long ans = 1;
  for (unsigned long long i = 2; i <= n; i++) {
    ans *= i;
  }
  return ans;
}

unsigned long long sigma(unsigned long long n, unsigned long long k, unsigned long long i) {
  if (n == 1) return 1;
  if (i == 1) return (k - 1) / fact(n-1) + 1;
  unsigned long long i_raw = sigma(n - 1, (k - 1) % fact(n-1) + 1, i - 1);
  return i_raw + (i_raw >= sigma(n, k, 1));
}

int main() {
  unsigned long long n, k;
  scanf("%llu%llu", &n, &k);
  for (unsigned long long i = 1; i <= n; i++) {
    printf("%llu ", sigma(n, k, i));
  }
  return 0;
}
