#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LOG2(x) (long long) log2( (double) (x)) + 1;

long long k_size, N_targ, n;
long long p_mod;
long long*** Arr_A;

void M_by_M_for_p(long long** X, long long** Y, long long*** R) {
    long long **Temp = (long long**) calloc(n, sizeof(long long*));
    for (long long i = 0; i < n; i++) {
        Temp[i] = (long long*) calloc(n, sizeof(long long));
    }

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            long long ans = 0;
            for (long long k = 0; k < n; k++) {
                ans = (((long long) X[i][k] * (long long) Y[k][j]) % p_mod + ans) % p_mod;
            }
            Temp[i][j] = (long long) ans;
        }
    }
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            (*R)[i][j] = Temp[i][j];
        }
    }
    for (long long i = 0; i < n; i++) {
        free(Temp[i]);
    }
    free(Temp);
}

int main(void) {
    n = 2;

    long long X[n], A[n][n];
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &X[n - 1 - i]);
    }

    scanf("%lld%lld", &N_targ, &p_mod);
    N_targ--;

    A[0][0] = 1;
    A[0][1] = 1;

    for (long long i = 1; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            if (i == j + 1)
                A[i][j] = 1;
            else
                A[i][j] = 0;
        }
    }

    if (N_targ <= k_size) {
        printf("%lld", X[n - 1 - N_targ + 1] % (long long) p_mod);
    }
    else {
        long long n_calc = N_targ - k_size;
        long long log2_n_calc = LOG2(n_calc);
        log2_n_calc += 2;
        //printf("%lld %lld\n", n_calc, log2_n_calc);

        Arr_A = (long long***) calloc (log2_n_calc, sizeof(long long**));
        for (long long i = 0; i < log2_n_calc; i++) {
            Arr_A[i] = (long long**) calloc(n, sizeof(long long*));
            for (long long j = 0 ; j < n; j++) {
                Arr_A[i][j] = (long long*) calloc(n, sizeof(long long));
            }
        }

        for (long long i = 0; i < n; i++) {
            for (long long j = 0; j < n; j++) {
                Arr_A[0][i][j] = ((i == j) ? 1 : 0);
                Arr_A[1][i][j] = A[i][j];
            }
        }

        for (long long i = 2; i < log2_n_calc; i++) {
            M_by_M_for_p(Arr_A[i - 1], Arr_A[i - 1], &Arr_A[i]);
        }
/*
    for (long long k = 0; k < log2_n_calc; k++) {
      printf("=======\n");
      for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
          printf("%lld ", Arr_A[k][i][j]);
        }
        printf("\n");
      }
    }
    printf("=======\n");
*/

        /*
        long long **A = (long long**) calloc(n, sizeof(long long*)), **B = (long long**) calloc(n, sizeof(long long*)), **C = (long long**) calloc(n, sizeof(long long*));
        for (long long i = 0; i < n; i++) {
          A[i] = (long long*) calloc(n, sizeof(long long));
          B[i] = (long long*) calloc(n, sizeof(long long));
          C[i] = (long long*) calloc(n, sizeof(long long));
        }
        //long long A[n][n], B[n][n], C[n][n];
        for (long long i = 0; i < n; i++) {
          for (long long j = 0; j < n; j++)
            scanf("%lld", &A[i][j]);
        }
        printf("=============\n");
        for (long long i = 0; i < n; i++) {
          for (long long j = 0; j < n; j++)
            scanf("%lld", &B[i][j]);
        }
        printf("=============\n");
        M_by_M_for_p(A, B, &C);
        for (long long i = 0; i < n; i++) {
          for (long long j = 0; j < n; j++) {
            printf("%lld ", C[i][j]);
          }
          printf("\n");
        } */

        long long *n_calc_in_2 = (long long*) calloc (log2_n_calc, sizeof(long long ));
        long long temp = n_calc;
        for (long long i = 0; i < log2_n_calc &&  temp > 0; i++) {
            n_calc_in_2[i] = temp % 2;
            temp /= 2;
        }
        /*
        for (long long i = 0; i < log2_n_calc; i++) {
          printf("%lld ", n_calc_in_2[i]);
        }
        printf("\n=======\n");
        */
        long long **Ans = (long long**) calloc(n, sizeof(long long*));
        for (long long i = 0; i < n; i++) {
            Ans[i] = (long long*) calloc(n, sizeof(long long));
            Ans[i][i] = 1;
        }

        for (long long i = 0; i < log2_n_calc; i++) {
            if (n_calc_in_2[i] == 1) {
                M_by_M_for_p(Ans, Arr_A[i + 1], &Ans);
            }
        }
        /*
        for (long long i = 0; i < n; i++) {
          for (long long j = 0; j < n; j++) {
            printf("%lld ", Ans[i][j]);
          }
          printf("\n");
        }
        */
        long long ans = 0;
        for (long long i = 0; i < n; i++) {
            //printf("%lld %lld\n", Ans[0][i], X[i]);
            //printf("%lld\n", ans);
            ans = (((long long) Ans[0][i] * (long long) X[i]) % p_mod + ans) % p_mod;
        }
        printf("%lld", ans);
    }
}
