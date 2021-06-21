#include <stdio.h>
#include <stdlib.h>

#define SIZE 31624

int* notprime, *primes;

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

int main(void) {
  primes = (int*) calloc(SIZE, sizeof(int));
  set_primes();

  int deg;
  scanf("%d", &deg);

  int pow_10[10];
  for (int i = 0; i < 10; i++)
    pow_10[i] = poww(10, i);

  int a, len, b;
  for (a = pow_10[deg-1]; a < pow_10[deg]; a++) {
    int is_giperprime = 1;
    for (len = 1; len <= deg; len++) {
      b = a / pow_10[deg - len];
      if (is_prime(b) == 0) {
        is_giperprime = 0;
        break;
      }
    }
    if (is_giperprime) {
      printf("%d ", a);
    }
  }

}
