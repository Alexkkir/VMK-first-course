#include <iostream>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  bool in_process = true, completed = false;

  int a[100][100];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  int sum;
  while(in_process = !completed) {
    // cheching rows
    for (int i = 0; i < n; i++) {
      sum = 0;
      for (int j = 0; j < m; j++) {
        sum += a[i][j];
      }
      if (sum < 0) {
        printf("l %d\n", i);
        for (int j = 0; j < m; j++) {
          a[i][j] = -a[i][j];
        }
      }
    }

    // cheching columns
    for (int j = 0; j < m; j++) {
      sum = 0;
      for (int i = 0; i < n; i++) {
        sum += a[i][j];
      }
      if (sum < 0) {
        printf("c %d\n", j);
        for (int i = 0; i < n; i++) {
          a[i][j] = -a[i][j];
        }
      }
    }

    // final check
    completed = true;
    for (int i = 0; i < n; i++) {
      sum = 0;
      for (int j = 0; j < m; j++) {
        sum += a[i][j];
      }
      if (sum < 0) {
        completed = false;
        break;
      }
    }
  }
}
