#include <stdio.h>
#include <stdlib.h>

#define LEN 5
typedef int TYPE[LEN];

int main() {
  TYPE a;
  for (int i = 0; i < 5; i++) {
    a[i] = i;
  }
  for (int i = 0; i < 5; i++) {
    printf("%d", a[i]);
  }
}
