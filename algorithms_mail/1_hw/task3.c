#include <stdio.h>
#include <stdlib.h>

unsigned int *length_arr;

static unsigned int n_of_digits(unsigned int x) {
  unsigned int deg = 0;
  unsigned int ten_deg = 1, ten_deg_pp = 10;
  while (!(ten_deg <= x && x < ten_deg_pp)) {
    ten_deg = ten_deg_pp;
    ten_deg_pp *= 10;
    deg++;
  }
  return deg + 1;
}

unsigned int calc_length(unsigned int n) {
  if (n == 1) return 1;
  if (length_arr[n - 1] != 0) return length_arr[n - 1];
  else return length_arr[n - 1] = calc_length(n - 1) * 2 + n_of_digits(n);
}

unsigned int ith_digit(unsigned int k, unsigned int n) {
  unsigned int l = n_of_digits(n);
  for (int i = 0; i < l - k; i++) {
    n /= 10;
  }
  return n % 10;
}

unsigned int fun(unsigned int n, unsigned int pos) {
  unsigned int n_10_l = n_of_digits(n);
  if (pos <= n_10_l) {
    return ith_digit(pos, n);
  }
  else if (pos <= n_10_l + calc_length(n - 1)) {
    return fun(n - 1, pos - n_10_l);
  }
  else {
    return fun(n - 1, calc_length(n) - pos + 1);
  }
}

int main() {
  unsigned int n, k, pos;
  scanf("%u%u", &n, &k);

  length_arr = (unsigned int*) calloc(30, sizeof(unsigned int));
  length_arr[0] = 1;

  for (unsigned int i = 0; i < k; i++) {
    scanf("%u", &pos);
    printf("%u", fun(n, pos));
  }

  // for (int i = 0; i < 30; i++) {
  //   printf("%lld\n", length_arr[i]);
  // }
  return 0;
}
