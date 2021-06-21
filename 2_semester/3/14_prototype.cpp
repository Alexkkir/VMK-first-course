#include <iostream>
#include <ctime>
#include <stdio.h>
using namespace std;

#define min(a, b) a < b ? a : b

int zeros_triv(int a, int k) {
  int ans = 0, y, zeros;
  for (int x = 1; x <= a; x++) {
    y = x;
    zeros = 0;
    while (y > 0) {
      zeros += !(y & 1);
      y >>= 1;
    }
    if (zeros == k) ans++;
  }
  return ans;
}

int bc(int k, int n) {
  if (k > n) return 0;
  // if (n == 0) return 0;
  if (k < 0) return 0;
  int d = min(n - k, k);
  int ans = 1;
  for (int i = 1; i <= d; i++) {
    ans *= (n - d) + i;
    ans /= i;
  }
  return ans;
}

int zeros_my(int num, int k) {
  unsigned l = 32, bit = 0x80000000, ans = 0;

  while ((num & bit) == 0) {
    bit >>= 1;
    l--;
  }

  ans += bc(k + 1, l - 1);
  l--;
  bit >>= 1;
  // printf("ans firstly %d\n", ans);
  while (l > 0 && k > 0) {
    if ((num & bit) == 0) {
      k--;
      if (k == 0 && l == 1) ans++;
    }
    else {
      ans += bc(k - 1, l - 1);
      if (k == 0) ans++;
      // printf("l %d\t k %d\t bit %d\t bc %d\n", l, k, bit, bc(k - 1, l - 1));
    }
    l--;
    bit >>= 1;
  }

  // if (k == 0)
  return ans;
}

int main() {
  srand(time(NULL));
  int k = 3;
  cout << zeros_my(16, 3);

  for (int i = 16; i <= 100; i++) {
    int ans1, ans2;
    ans1 = zeros_triv(i, k);
    ans2 = zeros_my(i, k);
    if (ans1 == ans2) {
      printf(".");
    }
    else {
      printf("\nn %d\tk%d\tans1 %d\tans2 %d\n", i, k, ans1, ans2);
    }
  }

}
