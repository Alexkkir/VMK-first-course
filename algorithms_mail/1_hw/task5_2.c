#include <stdlib.h>
#include <stdio.h>

unsigned long long gcd (unsigned long long a, unsigned long long b) {
  unsigned long long t;
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
  unsigned long long n;
  scanf("%d", &n);
  unsigned long long x_p, x_c;
  unsigned long long nod, k;

  unsigned long long sum = 0;
  scanf("%d", &x_p);
  for (unsigned long long i = 0; i < n - 1; i++) {
    scanf("%d", &x_c);
    nod = gcd(x_p, x_c);
    if (nod != 1) sum++;
    x_p = x_c;
  }
  printf("%d", sum);
}
