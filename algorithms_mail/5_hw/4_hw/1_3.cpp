#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define max(a, b) (a > b) ? a : b

int main() {
  int max_vol, n_chapt, size;
  scanf("%d%d", &max_vol, &n_chapt);
  int *a = (int*) malloc (n_chapt * sizeof(int));

  int max_size = 0;
  int sum_size = 0;
  for (int i = 0; i < n_chapt; i++) {
    scanf("%d", &a[i]);
    max_size = max(a[i], max_size);
    sum_size += a[i];
  }
  int ch_size = max(max_size, sum_size / n_chapt);
  while(1) {
    int buffer = 0, count = 1, succ = 1, rest = ch_size * max_vol - sum_size;
    for (int i = 0; i < n_chapt; i++) {
      if (buffer + a[i] <= ch_size) {
        buffer += a[i];
      }
      else {
		rest -= ch_size - buffer;
        buffer = a[i];
        count++;
      }
	  if (count > max_vol) {
		  succ = 0;
		  break;
	  }
	  if (rest < 0) {
		  succ = 0;
		  break;
	  }
	  // printf("i: %d\t buffer: %d\tcount: %d\n", i, buffer, count);
    }
    if (succ == 1) {
      printf("%d", ch_size);
      break;
    }
	else {
		ch_size++;
	}
  }
}
