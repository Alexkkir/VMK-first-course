#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LOG2(x) (int) log2( (double) (x)) + 1;
int k_size, N_targ, n;
long long p_mod;
int*** Arr_A;

void M_by_M_for_p(int** X, int** Y, int*** R) {
  int **Temp = (int**) calloc(n, sizeof(int*));
  for (int i = 0; i < n; i++) {
    Temp[i] = (int*) calloc(n, sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      long long ans = 0;
      for (int k = 0; k < n; k++) {
        ans = (((long long) X[i][k] * (long long) Y[k][j]) % p_mod + ans) % p_mod;
      }
      Temp[i][j] = (int) ans;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      (*R)[i][j] = Temp[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    free(Temp[i]);
  }
  free(Temp);
}

int main(void) {
  scanf("%d%d%lld", &k_size, &N_targ, &p_mod);
  n = k_size;

  int X[n], A[n][n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &X[n - 1 - i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[0][i]);
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j + 1)
        A[i][j] = 1;
      else
        A[i][j] = 0;
    }
  }

  if (N_targ <= k_size) {
    printf("%d", X[n - 1 - N_targ + 1] % (int) p_mod);
  }
  else {
    int n_calc = N_targ - k_size;
    int log2_n_calc = LOG2(n_calc);
    log2_n_calc += 2;
    //printf("%d %d\n", n_calc, log2_n_calc);

    Arr_A = (int***) calloc (log2_n_calc, sizeof(int**));
    for (int i = 0; i < log2_n_calc; i++) {
      Arr_A[i] = (int**) calloc(n, sizeof(int*));
      for (int j = 0 ; j < n; j++) {
        Arr_A[i][j] = (int*) calloc(n, sizeof(int));
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Arr_A[0][i][j] = ((i == j) ? 1 : 0);
        Arr_A[1][i][j] = A[i][j];
      }
    }

    for (int i = 2; i < log2_n_calc; i++) {
      M_by_M_for_p(Arr_A[i - 1], Arr_A[i - 1], &Arr_A[i]);
    }
/*
    for (int k = 0; k < log2_n_calc; k++) {
      printf("=======\n");
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          printf("%d ", Arr_A[k][i][j]);
        }
        printf("\n");
      }
    }
    printf("=======\n");
*/

    /*
    int **A = (int**) calloc(n, sizeof(int*)), **B = (int**) calloc(n, sizeof(int*)), **C = (int**) calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
      A[i] = (int*) calloc(n, sizeof(int));
      B[i] = (int*) calloc(n, sizeof(int));
      C[i] = (int*) calloc(n, sizeof(int));
    }
    //int A[n][n], B[n][n], C[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        scanf("%d", &A[i][j]);
    }
    printf("=============\n");
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        scanf("%d", &B[i][j]);
    }
    printf("=============\n");
    M_by_M_for_p(A, B, &C);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%d ", C[i][j]);
      }
      printf("\n");
    } */

    int *n_calc_in_2 = (int*) calloc (log2_n_calc, sizeof(int ));
    int temp = n_calc;
    for (int i = 0; i < log2_n_calc &&  temp > 0; i++) {
      n_calc_in_2[i] = temp % 2;
      temp /= 2;
    }
    /*
    for (int i = 0; i < log2_n_calc; i++) {
      printf("%d ", n_calc_in_2[i]);
    }
    printf("\n=======\n");
    */
    int **Ans = (int**) calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
      Ans[i] = (int*) calloc(n, sizeof(int));
      Ans[i][i] = 1;
    }

    for (int i = 0; i < log2_n_calc; i++) {
      if (n_calc_in_2[i] == 1) {
        M_by_M_for_p(Ans, Arr_A[i + 1], &Ans);
      }
    }
    /*
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%d ", Ans[i][j]);
      }
      printf("\n");
    }
    */
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      //printf("%d %d\n", Ans[0][i], X[i]);
      //printf("%lld\n", ans);
      ans = (((long long) Ans[0][i] * (long long) X[i]) % p_mod + ans) % p_mod;
    }
    printf("%lld", ans);
  }
}
