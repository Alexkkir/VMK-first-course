#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short get_i_bit(short x, int i) {
  return (x & (1 << i)) >> i;
}

char* sumall(short *a) {
  short sum = 0;
  short *tmp = a;
  while (*tmp) {
    sum += *tmp;
    tmp++;
  }
  int len = 8 * sizeof(short);
  printf("%d\n", sum);
  char *sum_str = (char*) calloc(len + 1, sizeof(char)); // len + 1 // надо ли увеличивать длину строки на один для символа конца строки?
  for (int i = 0; i < len; i++) {
    sum_str[i] = (char) get_i_bit(sum, len - i - 1) + '0';
  }
  sum_str[len] = '\0';
  return sum_str;
}


int main() {
  short a[] = {-1, 0, 100};
  printf("%s\n", sumall(a));
}
