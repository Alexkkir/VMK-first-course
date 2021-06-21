#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef node {
  char string[22];
}

int main(void) {
  node* A = (node*) malloc (1000000 * sizeof (node));
  int* B   = (int*) calloc (1000000, sizeof(int));
  int n = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%s", A[i].string);
  }

  int k;
  scanf("%d", &k);

  for (int i = 0; i < k; i++) {
    scanf("%d")
  }
}
