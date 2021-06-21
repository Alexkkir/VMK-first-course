#include <stdio.h>
#include <stdlib.h>

int n, m;
int** A;

void infect(int x, int y, int value){
  int i, j;
  for (i = x - 1; i <= x + 1; i++){
    for (j = y - 1; j <= y + 1; j++){
      if (0 <= i && i < n && 0 <= j && j < m && A[i][j] == 0 && (i == x || j == y)){
        A[i][j] = value;
      }
    }
  }
}

void print(void){
  printf("===========================\n");
  for(int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}

int fully_infected(void){
  int completely_infected = 1;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      if (A[i][j] == 0)
        completely_infected = 0;
    }
  }
  return completely_infected;
}

int main (void){
  int i, j;
  scanf("%d%d", &n, &m);
  A = (int**) calloc(n, sizeof(int*));
  for (i = 0; i < n; i++){
    A[i] = (int*) calloc(m, sizeof(int));
  }
  /*
  print();
  infect(3, 3);
  print();
  */
  int k, x, y;
  scanf("%d", &k);
  for (i = 0; i < k; i++){
    scanf("%d%d", &x, &y);
    A[x - 1][y - 1] = 1; //1 - infected; 0 - healthy;
  }

  int epoch;

  for (epoch = 0; fully_infected() == 0; epoch++){
    for (i = 0; i < n; i++){
      for (j = 0; j < m; j++){
        if (0 < A[i][j] && A[i][j] <= epoch + 1){
          infect(i, j, epoch + 2);
        }
      }
    }
  }
  printf("%d\n", epoch);
}
