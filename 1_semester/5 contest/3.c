#include <stdio.h>
#include <stdlib.h>

#define SIZE 1e6

int main (void)
{
  long long *A = (long long*) calloc(SIZE, sizeof(long long));
  static long long x;
  static long long i = 0, n = 0;
  do {
    scanf("%lld", &x);
    if (x == 0) break;
    A[i] = x;
    i++;
    n++;
  } while(1);

  for(i = 0; i < n; i += 2)
  {
    printf("%lld ", A[i]);
  }
  for(i = 1; i < n; i += 2)
  {
    printf("%lld ", A[i]);
  }
  free(A);
}
