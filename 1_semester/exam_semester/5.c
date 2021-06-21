#include <stdio.h>
#include <stdlib.h>

int main() {
  long long n = 176;
  long long ans = n * (n-1) * (n-2) * (n-1) * (n-2);
  printf("%lld", ans);
}
