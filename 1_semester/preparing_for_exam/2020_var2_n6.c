#include <stdio.h>
#include <stdlib.h>

int alldiv(int *a, int n) {
  for (int div = n; div >= 1; div--) {
    if (n % div != 0) continue;
    int div_was_found = 0;
    for (int i = 0; a[i]; i++) {
      if (a[i] == div) {
        div_was_found = 1;
        break;
      }
    }
    if (div_was_found == 0) {
      return div;
    }
  }
  return 0;
}

int main() {
  int a[] = {1, 2, 3, 55, 10, 11, 12, 0};
  int n = 10;
  printf("%d", alldiv(a, n));
}
