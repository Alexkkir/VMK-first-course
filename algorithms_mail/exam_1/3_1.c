#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a > b) ? a : b

typedef struct time_with_label {
  char time[100];
  enum {
    START,
    END
  } status;
} time_with_label;

int first_lower(time_with_label x, time_with_label y) {
  // printf("%d", strcmp(x.time, y.time));
  return strcmp(x.time, y.time) == -1;
}

static void QuickSort (time_with_label **a, int left, int right) {
  /* comp -- компаранд, i, j -- значения индексов */
  time_with_label *comp, *tmp;
  int i, j;
  i = left; j = right;
  comp = a[(left + right)/2];
  do {
    while (first_lower(*a[i], *comp) && i < right)
      i++;
    while (first_lower(*comp, *a[j]) && j > left)
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

void Qsort (time_with_label **a, int n) {
  QuickSort (a, 0, n - 1);
}


int first_lower_2(time_with_label x, time_with_label y) {
  // printf("%d", strcmp(x.time, y.time));
  return x.status == START ? 0 : 1;
}

static void QuickSort_2 (time_with_label **a, int left, int right) {
  /* comp -- компаранд, i, j -- значения индексов */
  time_with_label *comp, *tmp;
  int i, j;
  i = left; j = right;
  comp = a[(left + right)/2];
  do {
    while (first_lower_2(*a[i], *comp) && i < right)
      i++;
    while (first_lower_2(*comp, *a[j]) && j > left)
      j--;
    if (i <= j) {
      tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++, j--;
    }
  } while (i <= j);
  if (left < j) {
    QuickSort_2 (a, left, j);
  }
  if (i < right) {
    QuickSort_2 (a, i, right);
  }
}

void Qsort_2 (time_with_label **a, int n) {
  QuickSort_2 (a, 0, n - 1);
}

int main(void) {
  int n;
  scanf("%d", &n);

  time_with_label **a;
  a = (time_with_label**) calloc(2 * n, sizeof(time_with_label*));

  for (int i = 0; i < 2* n; i++) {
    a[i] = (time_with_label*) calloc(1, sizeof(time_with_label));
  }

  for (int i = 0; i < n * 2; i = i + 2) {
    char s1[100], s2[100];
    scanf("%s%s", &(*a[i]).time, &(*a[i + 1]).time);

    a[i]->status = START;
    a[i + 1]->status = END;
  }
  // printf("===\n");
  // Qsort_2(a, 2 * n);
  Qsort(a, 2 * n);
  // printf("===\n");

  int count = 0, max_count = 0, i = 0;
  int i_now = 0;

  while (i < 2 * n) {
    int ends = 0, starts = 0;
    while(i < 2 * n && i_now < 2 * n && strcmp(a[i_now]->time, a[i]->time) == 0) {
      if (a[i]->status == END)
        ends++;
      else
        starts++;
      i++;
    }
    i_now = i;
    count += starts;
    max_count = max(count, max_count);
    count -= ends;
  }

  printf("%d", max_count);

  // for (int i = 0; i < 2 * n; i++) {
  //   printf("%s\n", a[i]->time);
  // }

  // printf("\nend");
  return 0;
}
