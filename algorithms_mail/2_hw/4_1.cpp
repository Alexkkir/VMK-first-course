#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
  // FILE *f = fopen("inp.txt", "r");
  int n, m;
  scanf("%d%d", &n, &m);

  int a[100][100], sums_of_rows[100], sums_of_columns[100];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  int row_lim = 1 << n, col_lim = 1 << m;
  for (int row_gen = 0; row_gen < row_lim; row_gen++) {
    for (int col_gen = 0; col_gen < col_lim; col_gen++) {
      // проверяем позитивность

      memset(sums_of_rows, 0, sizeof(int) * 100);
      memset(sums_of_columns, 0, sizeof(int) * 100);

      int i, j;
      int row_pos, col_pos;

      for (i = 0, row_pos = row_gen; i < n; i++, row_pos >>= 1) {

        for (j = 0, col_pos = col_gen; j < m; j++, col_pos >>= 1) {
          // printf("%d%d\n", i, j);
          sums_of_rows[i] += a[i][j] * (1 - 2 * ((row_pos & 1) ^ (col_pos & 1)));
          sums_of_columns[j] += a[i][j] * (1 - 2 * ((row_pos & 1) ^ (col_pos & 1)));
        }
      }



      bool is_pos = true;
      for (i = 0; is_pos == true && i < n; i++)
        is_pos = (sums_of_rows[i] >= 0) ? true : false;
      for (j = 0; is_pos == true && j < m; j++)
        is_pos = (sums_of_columns[j] >= 0) ? true : false;

      // печать
      if (is_pos == true) {
        for (i = 0, row_pos = row_gen; row_pos != 0; i++, row_pos >>= 1) {
          if (row_pos & 1 == 1) {
            printf("l %d\n", i);
          }
        }
        for (j = 0,  col_pos = col_gen; col_pos != 0; j++, col_pos >>= 1) {
          if (col_pos & 1 == 1) {
            printf("c %d\n", j);
          }
        }
        return 0;
      }

    }
  }
  // printf("Impossible");
}
