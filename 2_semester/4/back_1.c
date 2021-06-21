#include <stdio.h>
#include <stdlib.h>

void rec(void);

unsigned int eax;
void f(void) {
  if (eax != 0) {
    rec();
    
  }
  eax = 1;
  return;
}

void rec(void) {
  eax--;
  f();
  eax *= 3;
  return;
}

int main(void) {
  scanf("%u", &eax);
  f();
  printf("%u", eax);
}
