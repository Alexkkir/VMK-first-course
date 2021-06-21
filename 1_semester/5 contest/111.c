#include <stdio.h>
#include <stdlib.h>
int main (void) {
  long long n;
  scanf("%lld", &n);

  long long i, j;

  long long ***A = (long long***) malloc(n * sizeof(long long**));
  for (i = 0; i < n; i++)
  {
        A[i] = (long long**) malloc(n * sizeof(long long*));
        for (j = 0; j < n; j++)
        {
          A[i][j] = (long long*) malloc(2 * sizeof(long long*));
        }
  }

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      scanf("%lld %lld", &A[i][j][0], &A[i][j][1]);
    }
  }
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        printf("%lld %lld ", A[j][i][0], -A[j][i][1]);
      }
      printf("\n");
    }

  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      free(A[i][j]);
    }
    free(A[i]);
  }
  free(A);
}
