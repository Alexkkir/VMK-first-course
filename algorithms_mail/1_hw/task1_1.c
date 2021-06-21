#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (a < b) ? a : b
int main() {
  int n;
  scanf("%d", &n);
  int q = 0;
  int min_q = 0;
  int x;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    if (x == 5) {
      q += 1;
    }
    if (x == 10) {
      q -= 1;
    }
    if (x == 50) {
      q -= 9;
    }
    if (x == 100) {
      q -= 19;
    }

    min_q = min(min_q, q);
  }

  printf("%d", -min_q);
  return 0;
}
