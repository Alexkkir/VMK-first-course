#include <stdio.h>
#include <stdlib.h>

int main(void) {
  unsigned eax, ebx = 0xffffffff;
  while(1) {
    scanf("%u", &eax);
    if (eax == 0) {
      break;
    }
    if (eax > ebx) {
      continue;
    }
    ebx = eax;
  }
  printf("%u", ebx);
  eax = 0;
  return 0;
}
