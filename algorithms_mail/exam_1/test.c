#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char a[100], b[100];

  scanf("%s%s", &a, &b);
  printf("%s %s\n", a, b);
  printf("%d", strcmp(a, b));
}
