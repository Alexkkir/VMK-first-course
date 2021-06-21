#include <stdio.h>
#include <stdlib.h>

int gcd (int a, int b) {
	while (b) {
		a %= b;
		int tmp = a;
    a = b;
    b = tmp;
	}
	return a;
}

int main() {
  int p, q;
  scanf("%d%d", &p, &q);

  int nod = gcd(p, q);
  p /= nod;
  q /= nod;

  int num = 2;
  while (p != 0) {
    // printf("p, q %d %d\n", p, q);
    p *= num;
    nod = gcd(p, q);
    p /= nod;
    q /= nod;

    printf("%d ", p / q);

    p %= q;
    num++;
  }
}
