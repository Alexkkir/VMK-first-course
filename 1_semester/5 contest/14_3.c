#include <stdio.h>
#include <stdlib.h>

#define SIZE 31624

int* notprime, *primes;
int deg;

void eratosfen(void) {
  notprime[0] = 1;
  notprime[1] = 1;
  for (int i=2; i<=SIZE; i++) {
  	if (!notprime[i]) {
			for (int j=i*i; j<= SIZE; j+=i) {
				notprime[j] = 1;
      }
    }
  }
}

void set_primes(void) {
  int i = 1, x = 3;
  primes[0] = 2;
  while (i < SIZE) {
    int probably_prime = 1;
    for (int j = 0; j < SIZE && primes[j] * primes[j] <= x; j++) {
      if (x % primes[j] == 0) {
        probably_prime = 0;
        break;
      }
    }
    if (probably_prime == 1) {
      primes[i] = x;
      i++;
    }
    x++;
  }
}

/*
int is_prime(int x) {
  if (x <= SIZE - 2)
    return (notprime[x] + 1 ) % 2;
  else {
    int probably_prime = 1;
    for (int i = 0; i < SIZE; i++) {
      if (notprime[i] == 0 && x % i == 0) {
        probably_prime = 0;
        break;
      }
    }
    return probably_prime;
  }
}
*/
int is_prime(int x) {
  if (x == 0)
    return 0;
  if (x == 1)
    return 0;
  int probably_prime = 1;
  for (int i = 0; i < SIZE && primes[i] * primes[i] <= x; i++) {
    if (x % primes[i] == 0) {
      probably_prime = 0;
      break;
    }
  }
  return probably_prime;
}

int poww(int a, int n) {
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans *= 10;
  }
  return ans;
}

void rec(int x, int len) {
  //printf("\n%d %d\n", x, len);
  if (len == deg) {
    printf("%d ", x);
    return;
  }
  for (int i = 0; i < 10; i++) {
    int y = 10 * x + i;
    if (is_prime(y)) {
      rec(y, len + 1);
    }
  }
}

int main(void) {
  primes = (int*) calloc(SIZE, sizeof(int));
  set_primes();

  scanf("%d", &deg);

  rec(0, 0);

}
