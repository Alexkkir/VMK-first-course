#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
  char string[110];
  int number;
} node;

int main(void) {

  FILE *inp = fopen("input.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  node* A = (node*) malloc (102 * sizeof(node));
  int n = 0;
  while(!feof(int)) {
  //while (n < 3) {
    fscanf(inp, "%s %d", &A[n].string, &A[n].number);
    //scanf("%s %d", &A[n].string, &A[n].number);
    n++;
  }
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 0; A[j].number != i && j < n; j++);
    //printf("%s ", A[j].string);
    fprintf(outp, "%s ", A[j].string);
  }

  /*
  fclose(inp);
  fclose(outp);
  */
  free(A);
}
