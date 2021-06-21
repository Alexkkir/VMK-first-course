#include <stdlib.h>
#include <stdio.h>

int main(void) {
  FILE *inp = fopen("input.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  int n, k;
  fscanf(inp, "%d%d", &n, &k);
  int *a = (int*) calloc(n, sizeof(int));
  int *bank = (int*) calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    a[i] = i + 1;
  }
  int first_val, last_val, first_ind, last_ind;
  for (int evol = 0; evol < k; evol++) {
    fscanf(inp, "%d%d", &first_val, &last_val);

    int r;
    for (r = 0; a[r] != first_val; r++);
    first_ind = r;
    for(; a[r] != last_val; r++);
    last_ind = r + 1;
    //printf("%d %d\n", first_ind, last_ind);

    if (first_ind == 0) {
      continue;
    }

    for (int j = 0; j < first_ind; j++) {
      bank[j] =a[j];
    }

    for (int j = 0; j < last_ind - first_ind; j++) {
      a[j] = a[j + first_ind];
    }
    for (int j = last_ind - first_ind; j < last_ind; j++) {
      a[j] = bank[j - (last_ind - first_ind)];
    }

  }
  for (int i = 0; i < n; i++) {
    fprintf(outp, "%d ", a[i]);
  }


  fclose(inp);
  fclose(outp);
}
