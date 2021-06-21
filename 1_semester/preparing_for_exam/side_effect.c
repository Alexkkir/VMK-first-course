#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int x = 42, y = -105;
  int ans = (y = 1) && (y = 0);
  printf("%d %d %d ", ans, x, y);
}
