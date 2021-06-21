#include <stdio.h>
#include <stdlib.h>

int main(void) {
  unsigned eax, ebx = 0xffffffff;
again:
  scanf("%u", &eax);
  if (eax == 0) {
    goto exit;
  }
  if (eax > ebx) {
    goto again;
  }
  ebx = eax;
  goto again;
exit:
  printf("%u", ebx);
  eax ^= eax;
  return 0;
}
