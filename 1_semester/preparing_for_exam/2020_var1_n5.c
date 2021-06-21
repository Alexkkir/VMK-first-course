#include <stdlib.h>
#include <stdio.h>

typedef char str[2020];


int main() {
  str mtx[1701], *ptr = mtx + 1;
  // long long int x = (char*) (&mtx[0]) - (char*)ptr;
  // printf("%lld", x);
  int x = (mtx = malloc (2020*42));
  printf("%d", !!(mtx = malloc (2020*42)));
}
