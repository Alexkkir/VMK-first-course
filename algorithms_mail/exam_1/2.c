#include <stdio.h>
#include <stdlib.h>


int comp (const int *i, const int *j)
{
return *i - *j;
}

int main() {
  int l, n;
  scanf("%d%d", &l, &n);

  int **a1;
  a1 = (int**) calloc(n, sizeof(int*));
  for (int i = 0; i < n; i++) {
    a1[i] = (int*) calloc(2, sizeof(int));
  }

  int *used;
  a1 = (int*) calloc(n, sizeof(int));

  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a1[i][0] = x - l;
    a1[i][1] = x + l;
  }

  qsort(a1, n, sizeof(int), (int(*) (const void *, const void *)) comp)
}
