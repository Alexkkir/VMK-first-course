#include <stdio.h>
#include <stdlib.h>
int main (void) {
int *p = (int*) malloc (sizeof(int));
int *q = (int*) realloc (p, sizeof(int));
*p = 1;
*q = 2;
if (p == q)
printf ("%d %d\n", *p, *q);
return 0;
}
