#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;


long long invs = 0;
long long *aux;

void merge(long long *a, long long left, long long mid, long long right) {
  if (left == right) return;
  for (long long k = left; k < mid; k++) aux[k] = a[k];
  for (long long k = right - 1; k >= mid; k--) aux[k] = a[right + mid - 1 - k];

  // printf("left: %d\tright %d\naux:\t", left, right);
  // for (long long i = left; i < right; i++) {
  //   printf("%d ", aux[i]);
  // }
  // printf("\n");

  long long i = left, j = right - 1;

  for (long long k = left; k < right; k++) {
    if (aux[i] <= aux[j]) {
      a[k] = aux[i];
      i++;
    }
    else {
      long long add = ((i != j) ? mid - i : 0);
      // printf("i: %d\t aux[i]: %d\t j: %d\t aux[j]: %d\t, +invs: %d\n", i, aux[i], j, aux[j], add);
      a[k] = aux[j];
      invs += add;
      j--;
    }
  }
}

void merge_sort(long long *a, long long left, long long right) {
  // printf("left: %d\t right: %d\na:\t");
  // for (long long i = left; i < right; i++) printf("%d ", a[i]);
  // printf("\n");

  if (left == right || left == right - 1) return;
  long long mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

long long inv_tr(long long *a, long long n) {
  long long count = 0;
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < i; j++) {
      if (a[j] > a[i]) count++;
    }
  }
  return count;
}

int main() {
  long long n;
  scanf("%lld", &n);
  // n = 1000;
  long long *a = new long long[n];
  aux = new long long[n];

  for (long long i = 0; i < n; i++) scanf("%lld", &a[i]);
  merge_sort(a, 0, n);
  printf("%lld", invs);


  // for (long long epoch = 0; epoch < 10000; epoch++) {
  //   for (long long i = 0; i < n; i++) {
  //     a[i] = rand() % 10;
  //   }
  //   invs = 0;
  //   long long my_inv = inv_tr(a, n);
  //   merge_sort(a, 0, n);
  //   if (invs != my_inv) {
  //     printf("\ncorr: %d\t my: %d\n", my_inv, invs);
  //     for (long long k = 0; k < n; k++) printf("%d ", a[k]);
  //     break;
  //   }
  //   else printf(".");
  // }

  // long long ex[] = {1, 7, 4, 0, 9, 4};
  // for (long long i = 0; i < n; i++) a[i] = ex[i];
  // printf("corr: %d\n", inv_tr(a, n));
  //
  // merge_sort(a, 0, n);
  //
  // printf("\ninvs: %d\narray: ", invs);
  // for (long long i = 0; i < n; i++) {
  //   printf("%d ", a[i]);
  // }
}
