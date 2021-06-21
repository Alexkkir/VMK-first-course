#include <string.h>
#include <stdlib.h>

int fib(int n) {
  if (n == 1) {
    return 1;
  }
  if (n == 2) {
    return 1;
  }
  else {
    return fib(n-1) + fib(n-2);
  }
  return 0;
}

int sum_fib_n(int n) {
  int sum = 0;
  if (n == 0) return 0;

  for (int i = 1; i <= n; i++) {
    sum += fib(i);
  }
  return sum;
}

int i_lays_in_2div_str(int i) {
  int n_min;
  i = i + 1;
  for (n_min = 0; sum_fib_n(n_min + 1) < i ; n_min++);
  return n_min % 2;
}

char* fibocci(char* s) {
  int n = strlen(s);
  char *ans = (char*) calloc(n + 1, sizeof(char));
  int i_s, i_ans = 0;
  for (i_s = 0; i_s < n; i_s++) {
    if (i_lays_in_2div_str(i_s)) {
      ans[i_ans] = s[i_s];
      i_ans++;
    }
  }
  int len_ans = i_ans;
  ans = realloc(ans, len_ans + 1);
  ans[len_ans] = '\0';
  return ans;
}
