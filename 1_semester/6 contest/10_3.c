#include <stdlib.h>
#include <stdio.h>

int main(void) {
  FILE *inp = fopen("input.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  int n, k;
  fscanf(inp, "%d%d", &n, &k);
  // scanf("%d%d", &n, &k);

  int a[n + 1][2], head = 1, tail = n;
  for (int i = 1; i <= n; i++) {
    if (i == 1) {
      a[i][0] = n;
      a[i][1] = 2;
    }
    else if (i == n) {
      a[i][0] = n - 1;
      a[i][1] = 1;
    }
    else {
      a[i][0] = i - 1;
      a[i][1] = i + 1;
    }
  }

  int first, last;
  for (int i = 0; i < k; i++) {
    fscanf(inp, "%d%d", &first, &last);
    // scanf("%d%d", &first, &last);
    if (first != head) {
      if (last != tail) {
        a[a[first][0]][1] = a[last][1];
        a[a[last][1]][0] = a[first][0];
        a[last][1] = head;
        a[head][0] = last;
        a[first][0] = tail;
        a[tail][1] = first;
        head = first;
      }
      else {
        a[last][1] = head;
        a[head][0] = last;
        tail = a[first][0];
        head = first;
      }
    }
  }
  int tmp = head;
  for (int i = 0; i < n; i++) {
    fprintf(outp, (i == n) ? "%d" : "%d ", tmp);
    // printf((i == n) ? "%d" : "%d ", tmp);
    tmp = a[tmp][1];
  }
  fclose(inp);
  fclose(outp);
}
