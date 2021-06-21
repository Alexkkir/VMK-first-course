#include <stdio.h>

int main() {
  int i, sum;
  for (i = 0, sum = 0; i++, i < 100; sum += i);
  printf("%d %d ");
}
