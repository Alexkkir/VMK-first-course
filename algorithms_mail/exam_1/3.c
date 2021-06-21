#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct time_with_label {
  char time[100];
  enum {
    START,
    END
  } status;
} time_with_label;

static void QuickSort (time_with_label *a, int left, int right) {
  /* comp -- компаранд, i, j -- значения индексов */
  time_with_label comp, tmp;
  int i, j;
  i = left; j = right;
  comp = a[(left + right)/2];

  printf("%s", comp.time);

  // do {
  //   while (first_bigger(comp, a[i]) && first_bigger(right, i))
  //     i++;
  //   while (first_bigger(a[j], comp) && first_bigger(j, left))
  //     j--;
  //   if (i <= j) {
  //     tmp = a[i];
  //     a[i] = a[j];
  //     a[j] = tmp;
  //     i++, j--;
  //   }
  // } while (i <= j);
  if (left < j) {
    QuickSort (a, left, j);
  }
  if (i < right) {
    QuickSort (a, i, right);
  }
}

void Qsort (time_with_label *a, int n) {
  QuickSort (a, 0, n - 1);
// }

int first_bigger(time_with_label x, time_with_label y) {
  return strcmp(x.time, y.time);
}

int main(void) {
  int n;
  scanf("%d", &n);

  time_with_label *a;
  a = (time_with_label*) calloc(n, sizeof(time_with_label));

  for (int i = 0; i < n * 2; i = i + 2) {
    char s1[100], s2[100];
    scanf("%s%s", &a[i].time, &a[i + 1].time);
    a[i].status = START;
    a[i + 1].status = END;
    // 2 02:03:42 13:54:01 13:54:01 01:02:34
  }
  Qsort(a, n);
  
  return 0;
}
