#include <stdlib.h>
#include <stdio.h>

int gcd (int a, int b) {
  int t;
  if (a < b) {
    t = a;
    a = b;
    b = t;
  }
	while (b) {
		a %= b;
    t = a;
    a = b;
    b = t;
	}
	return a;
}

int main() {
  int n;
  scanf("%d", &n);
  int x_p, x_c;
  int nod, k;

  int sum = 0;
  scanf("%d", &x_p);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &x_c);
    nod = gcd(x_p, x_c);
    if (nod != 1) sum++;      
    x_p = x_c;
  }
  printf("%d", sum);
}
