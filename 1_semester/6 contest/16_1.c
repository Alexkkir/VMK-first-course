#include <stdio.h>
#include <stdlib.h>

int comp (const int *i, const int *j)
{
return *i - *j;
}

int main(void) {
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  int *a = (int*) calloc(100000, sizeof(int));
  int n = 0;
  int x;
  while(!feof(input)) {
    if (fscanf(input, "%d", &x) > 0) {
      a[n++] = x;
    }
  }
  qsort(a, n, sizeof(int), (int(*) (const void *, const void *)) comp);
  for (int i = 0; i < n; i++) {
    fprintf(output, "%d ", a[i]);
  }
  fclose(input);
  fclose(output);
}
