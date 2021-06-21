#include <stdlib.h>
#include <stdio.h>



typedef struct node {
  int** matrix;
  long long trace;
  int size;
} node;

int main(void) {
  int n_elems;
  scanf("%d", &n_elems);
  node* elem = (node*) malloc(n_elems * sizeof(node));
  int size = 0;
  long long max_trace = -9223372036854775807 - 1;
  int i_of_matrix_with_max_trace = 0;
  if (i_of_matrix_with_max_trace == 0) size++;

  for (int i = 0; i < n_elems; i++) {
    scanf("%d", &size);
    elem[i].matrix = (int**) malloc (size * sizeof (int*));
    for (int j = 0; j < size; j++) {
      elem[i].matrix[j] = (int*) malloc (size * sizeof (int));
    }
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        scanf("%d", &elem[i].matrix[j][k]);
      }
    }
    elem[i].size = size;
    elem[i].trace = 0;
    for (int j = 0; j < size; j++) {
      elem[i].trace += (long long) elem[i].matrix[j][j];
    }
    if (elem[i].trace > max_trace) {
      max_trace = elem[i].trace;
      i_of_matrix_with_max_trace = i;
    }
    //printf("%lld\n", elem[i].trace);
  }

  for (int i = 0; i < elem[i_of_matrix_with_max_trace].size; i++) {
    for (int j = 0; j < elem[i_of_matrix_with_max_trace].size; j++) {
      printf("%d ", elem[i_of_matrix_with_max_trace].matrix[i][j]);
    }
    printf("\n");
  }
}
