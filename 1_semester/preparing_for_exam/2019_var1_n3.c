#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int a = 18, b = -5;
  unsigned short u = 0x1920;
  char *ss[] = {"iam", "the", "walrus"};
  char *p = &ss[2][4], *q = *ss;
  struct S{
    char *s;
    struct S *n;
  } g[] ={ {ss[2], g}, {ss[1], g + 1} };

  int x = 3;
  x = x + x++;
  printf("%d", x);
}
