#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN_INT (-2147483647 - 1)
#define MAX_INT 2147483647

int n, m;
int **A, **B;

void set_value(int x, int y){
  int i, max = 0;
  for(i = x - 1; i <= x + 1; i++){
    if (0 <= i && i < n){
      max = MAX(max, B[i][y - 1]);
    }
  }
  B[x][y] = max + A[x][y];
}

int main (void){
  scanf("%d%d", &n, &m);
  int i, j;

  A = (int**) calloc(n, sizeof(int*));
  for (i = 0; i < n; i++){
    A[i] = (int*) calloc(m, sizeof(int));
  }

  B = (int**) calloc(n, sizeof(int*));
  for (i = 0; i < n; i++){
    B[i] = (int*) calloc(m, sizeof(int));
  }

  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++){
      scanf("%d", &A[i][j]);
    }
  }

  for(i = 0; i < n; i++)
    B[i][0] = A[i][0];

  for(j = 1; j < m; j++){
    for(i = 0; i < n; i++){
      set_value(i, j);
    }
  }

  int ans = 0;
  for(i = 0; i < n; i++){
    ans = MAX(ans, B[i][m - 1]);
  }
  printf("%d", ans);
}
