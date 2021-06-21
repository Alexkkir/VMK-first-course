#include <stdio.h>
#include <stdlib.h>

int nod(int a, int b) {
  int c;
  if (a < b) {
    c = a;
    a = b;
    b = c;
  }
  while(b) {
    c = b;
    b = a % b;
    a = c;
  }
  return a;
}

int is_prime(int n) {
  if (n == 1)
    return 0;
  int is_prime = 1;
  for (int i = 2; i < n / 2 + 1; i++){
    if (nod(n, i) != 1) {
      is_prime = 0;
      break;
    }
  }
  return is_prime;
}

int poww(int a, int n) {
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans *= 10;
  }
  return ans;
}

int main(void) {
  int deg;
  scanf("%d", &deg);
  for (int a = poww(10, deg - 1); a < poww(10, deg); a++) {
    int is_giperprime = 1;
    for (int len = 1; len <= deg; len++) {
      int b = a / (poww(10, deg - len));
      if (!is_prime(b)) {
        is_giperprime = 0;
        break;
      }
    }
    if (is_giperprime) {
      printf("%d ", a);
    }
  }
}
