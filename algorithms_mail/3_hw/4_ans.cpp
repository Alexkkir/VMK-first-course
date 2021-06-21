#include <cstdlib>

void fast_sort(unsigned *begin, unsigned *end) {
  size_t n = (size_t) (end - begin);

  unsigned countDigit[10];
  unsigned *b = (unsigned*) malloc(n * sizeof(unsigned));

  unsigned count = 0, tmp, dig, x;
  for (size_t d_i = 0; d_i < 35; d_i++) {
    for (unsigned j = 0; j < 10; j++) {
      countDigit[j] = 0;
    }
    for (size_t j = 0; j < n; j++) {
      x = *(begin + j);
      for (size_t i = 0; i < d_i; i++) x /= 10;
      dig = x % 10;
      countDigit[dig]++;
    }
    count = 0;
    for (size_t j = 0; j < 10; j++) {
      tmp = countDigit[j];
      countDigit[j] = count;
      count += tmp;
    }

    // for (int i = 0; i < 10; i++) {
    //   printf("%d ", countDigit[i]);
    // }
    // printf("\n");

    for (size_t j = 0; j < n; j++) {
      x = *(begin + j);
      for (size_t i = 0; i < d_i; i++) x /= 10;
      dig = x % 10;
      b[countDigit[dig]] = *(begin + j);
      countDigit[dig]++;
    }

    // for (int i = 0; i < n; i++) printf("%d ", b[i]); printf("\n");
    memcpy(begin, b, 4 * n);
  }
}
