#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// 2 1 3 4
// long long int, неубывание <=, Шелл, быстрая сортировка
#define MAX_LONG_LONG 9223372036854775807
#define abs(x) x > 0 ? x : -x

int* Shell(long long int *a, int n) { //сортировка Шелла
  int n_comparisons = 0, n_swaps = 0;

  int d = n;
  d = d / 2;
  int i, j;
  while (d > 0) {
    for (i=0; i < n - d; i++) {
      j = i;
      while (j >= 0 && ++n_comparisons && a[j] > a[j+d]) {
        long long int temp = a[j];
        a[j] = a[j+d];
        a[j+d] = temp;
        n_swaps++;
        j--;
      }
    }
    d=d/2;
  }
  int *result = (int *) malloc (2 * sizeof(int));
  result[0] = n_comparisons; result[1] = n_swaps;
  return result;
}

void QuickSort (long long int *a, int left, int right, int* p_n_comparisons, int* p_n_swaps) {
  /* comp -- компаранд, i, j -- значения индексов */
  long long int comp, tmp;
  int i, j;
  i = left; j = right;
  comp = a[(left + right)/2];
  do {
    while (i < right && ++(*p_n_comparisons) && a[i] < comp)
      i++;
    while (j > left && ++(*p_n_comparisons) && comp < a[j])
      j--;
    if (i <= j) {
      tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++, j--;
      (*p_n_swaps)++;
    }
  } while (i <= j);
  if (left < j) {
    QuickSort (a, left, j, p_n_comparisons, p_n_swaps);
  }
  if (i < right) {
    QuickSort (a, i, right, p_n_comparisons, p_n_swaps);
  }
}

int* Qsort (long long int *a, int n) {
  int n_comparisons = 0, n_swaps = 0;
  QuickSort (a, 0, n - 1, &n_comparisons, &n_swaps);

  int *result = (int *) malloc (2 * sizeof(int));
  result[0] = n_comparisons; result[1] = n_swaps;
  return result;
}

long long int* create_sorted_ascending_array(int n) {
  long long int *a = (long long int*) malloc (n * sizeof(long long int));
  for (long long int i = 0; i < (long long int) n; i++) {
    a[i] = i + 1;
  }
  return a;
}

long long int* create_sorted_descending_array(int n) {
  long long int *a = (long long int*) malloc (n * sizeof(long long int));
  for (long long int i = 0; i < (long long int) n; i++) {
    a[i] = n - i;
  }
  return a;
}

long long int* create_random_array(int n) {
  long long int *a = (long long int*) malloc (n * sizeof(long long int));
  for (long long int i = 0; i < (long long int) n; i++) {
    a[i] = abs(( ((long long int) rand()) * ((long long int) rand()) * ((long long int) rand()) * ((long long int) rand())) % MAX_LONG_LONG);
    a[i] = a[i] * (long long int) rand() * 2 - 1;
  }
  return a;
}

long long int* dublicate_arrow(long long *a, int n) {
  long long int *b = (long long int*) malloc (n * sizeof(long long int));
  for (long long int i = 0; i < (long long int) n; i++) {
    b[i] = a[i];
  }
  return b;
}

int main() {
char *locale = setlocale(LC_ALL, "");

  long long int *a;
  int n = 7;
  int n_values[] = {10, 20, 50, 100};
  int *result;
  printf("Shell sort\n");

  long long *a_1_rand = create_random_array(n_values[2]);
  long long *a_2_rand = create_random_array(n_values[2]);
  long long *a_1_rand_copy = dublicate_arrow(a_1_rand, n_values[3]);
  long long *a_2_rand_copy = dublicate_arrow(a_2_rand, n_values[3]);

  for (int i = 0; i < 4; i++) {
    float m_r0 = 0, m_r1 = 0;
    n = n_values[i];

    a = create_sorted_ascending_array(n);
    result = Shell(a, n);
    printf("ascending\t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    a = create_sorted_descending_array(n);
    result = Shell(a, n);
    printf("descending \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    result = Shell(a_1_rand, n);
    printf("random     \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    result = Shell(a_2_rand, n);
    printf("random     \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0], m_r1 += result[1];

    m_r0 /= 4; m_r1 /= 4;
    printf("                          \t medium_comp = %.1f \t medium swaps = %.1f\n", m_r0, m_r1);
    printf("\n");
  }
  printf("\nQuick sort\n");

  for (int i = 0; i < 4; i++) {
    float m_r0 = 0, m_r1 = 0;
    n = n_values[i];

    a = create_sorted_ascending_array(n);
    result = Qsort(a, n);
    printf("ascending\t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    a = create_sorted_descending_array(n);
    result = Qsort(a, n);
    printf("descending \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    result = Qsort(a_1_rand_copy, n);
    printf("random     \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0]; m_r1 += result[1];

    result = Qsort(a_2_rand_copy, n);
    printf("random     \t n = %d \t n_comparisons = %d \t n_swaps = %d\n", n, result[0], result[1]);
    m_r0 += result[0], m_r1 += result[1];

    m_r0 /= 4; m_r1 /= 4;
    printf("                           \t medium_comp = %.1f \t medium swaps = %.1f\n", m_r0, m_r1);
    printf("\n");
  }
  printf("\n");
}
