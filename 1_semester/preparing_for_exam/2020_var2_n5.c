#include <stdio.h>
#include <stdlib.h>


int main(void) {

  typedef int arr[101];

  arr mult[7], *ptr = &mult[1];
  int x = 1;
  struct {short a; char b[7];} s = {0};
  char c = '5', *pt = &s.b[2];

  int ans = 0;
  ans = (s.a=x--) || (s.b[3]+=17);
  printf("%d", ans);
}
