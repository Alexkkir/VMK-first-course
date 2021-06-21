
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
using std::vector;

#define SIZE 1000000000

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

unsigned get_digit(unsigned x, size_t i) {
  return i < 32 ? (x >> i) & 1 : 0;
}


unsigned get_digit_2deg(unsigned x, size_t i, unsigned deg) {
  // int mask = 0;
  // for (int i = 0; i < deg; i++) {
  //   mask = (mask << 1) + 1;
  // }
  int mask;
  // if (deg ==)
  return (x >> i * deg) & mask;
}

#include <cstdlib>

void fast_sort(unsigned *begin, unsigned *end) {
  size_t n = (size_t) (end - begin);

  const int deg = 4; // deg should be divider of 32
  const int base = 2 << deg;
  const int max_digit_ind = 32 / deg;
  unsigned mask;
  if (deg == 1) {mask = 0b1;}
  else if (deg == 2) {mask = 0b11;}
  else if (deg == 4) {mask = 0b1111;}
  else if (deg == 8) {mask = 0b11111111;}


  unsigned countDigit[base];
  unsigned *b = (unsigned*) malloc(n * sizeof(unsigned));

  unsigned count = 0, tmp, dig, x;
  for (size_t d_i = 0; d_i < max_digit_ind; d_i++) {
    for (unsigned j = 0; j < base; j++) {
      countDigit[j] = 0;
    }

    for (size_t j = 0; j < n; j++) {
      // dig = get_digit_2deg(*(begin + j), d_i, deg);
      dig = ((*(begin + j)) >> deg * d_i) & mask;
      countDigit[dig]++;
    }

    // for (int i = 0; i < base; i++) {
    //   printf("%d ", countDigit[i]);
    // }
    // printf("\n");

    count = 0;
    for (size_t j = 0; j < base; j++) {
      tmp = countDigit[j];
      countDigit[j] = count;
      count += tmp;
    }


    for (size_t j = 0; j < n; j++) {
      // dig = get_digit_2deg(*(begin + j), d_i, deg);
      dig = ((*(begin + j)) >> deg * d_i) & mask;
      b[countDigit[dig]] = *(begin + j);
      countDigit[dig]++;
    }

    // for (int i = 0; i < n; i++) printf("%d ", b[i]); printf("\n");
    memcpy(begin, b, 4 * n);
  }
  // free(digits);
  free(b);
}

int main() {
  unsigned array[8] = {3,1,4,1,5,9,2,6};
  fast_sort(array, array+8);
  // Now array = {1,1,2,3,4,5,6,9}
  for (int i = 0; i < 8; i++) {
    printf("%d ", array[i]);
  }

  // const int deg = 4; // deg should be divider of 32
  // const int base = 2 << deg;
  // const int max_digit_ind = 32 / deg;
  // unsigned mask;
  // if (deg == 1) {mask = 0b1;}
  // else if (deg == 2) {mask = 0b11;}
  // else if (deg == 4) {mask = 0b1111;}
  // else if (deg == 8) {mask = 0b11111111;}
  //
  // for (int i = 1; i < 100; i++) {
  //   printf("%d ", i);
  //   for (int j = max_digit_ind; j >= 0; j--) {
  //     int dig = (i >> deg * j) & mask;
  //     printf("%d ", dig);
  //   }
  //   printf("\n");
  // }
}
