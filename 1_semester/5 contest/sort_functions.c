#include <stdlib.h>
#include <stdio.h>

static void QuickSort (int *a, int left, int right);
void Qsort (int *a, int n);
void Qsort (int *a, int n);
int comp_rule (const int *i, const int *j);

int main(void) {

  int *A;
  const int size = 100;
  A = (int*) calloc(size, sizeof(int));
  for (int i = 0; i < size; i++) {
    A[i] = rand() % 10;
  }

  Qsort(A, size);  // моя фунция
  //qsort(A, size, sizeof(int), (int(*) (const void *, const void *)) comp_rule); // встроенная функция

  for (int i = 0; i < size; i++) {
    printf("%d ", A[i]);
  }

}

static void QuickSort (int *a, int left, int right) {
  /* comp -- компаранд, i, j -- значения индексов */
  int comp, tmp, i, j;
  i = left; j = right;
  comp = a[(left + right)/2];
  do {
    while (a[i] < comp && i < right)
      i++;
    while (comp < a[j] && j > left)
      j--;
    if (i <= j) {
      tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++, j--;
    }
  } while (i <= j);
  if (left < j) {
    QuickSort (a, left, j);
  }
  if (i < right) {
    QuickSort (a, i, right);
  }
}

void Qsort (int *a, int n) {
  QuickSort (a, 0, n - 1);
}

int comp_rule (const int *i, const int *j)
{
return *i - *j;
}
