#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN_INT (-2147483647 - 1)
#define MAX_INT 2147483647

int n, m, k;
int** B;

int main (void){
  int i, j;
  scanf("%d%d", &n, &m);

  int x, y;
  scanf("%d", &k);

  B = (int**) calloc(k, sizeof(int*));
  for (i = 0; i < k; i++){
    B[i] = (int*) calloc(2, sizeof(int));
  }

  for (i = 0; i < k; i++){
    scanf("%d%d", &y, &x );
    B[i][0] = x - 1;
    B[i][1] = y - 1;
  }

  int path_max = 0, path_cur_min, path_cur;

  for (i = 0; i < n; i++){
    for (j = 0; j < m; j++){
      path_cur_min = MAX_INT;
      for (int l = 0; l < k; l++){
        path_cur = abs(i - B[l][0]) + abs(j - B[l][1]);
        //printf("i=%d j=%d l=%d  abs(i - B[l][0])=%d abs(j - B[l][1])=%d path_cur=%d\n", i, j, l, abs(i - B[l][0]), abs(j - B[l][1]), path_cur);
        path_cur_min = MIN(path_cur, path_cur_min);
      }
      path_max = MAX(path_max, path_cur_min);
    }
  }

  printf("%d", path_max);
}
