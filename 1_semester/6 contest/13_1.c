#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct elem {
  enum {
    string,
    number
  } type;
  char string[102];
  int number;
} elem;

int k, n = 0, m = 0;
elem **a;
FILE *input, *output;

typedef enum state_type {
  reading_str,
  reading_num
} state_type;

int i = 0, j = 0;
char c;

int skip_spaces(void) {
  if(!feof(input)) {
    fscanf(input, "%c", &c);
    while (c == ' ') {
      fscanf(input, "%c", &c);
    }
    if (c == '\n') {
      n = i;
      return -1;
    }
  }
  else {
    n = i;
    return -1;
  }
  return 1;
}

state_type set_state(void) {
  if (c == '\"') {
    return reading_str;
  }
  else if (('0' <= c && c <= '9') || c == '-') {
    return reading_num;
  }
  else {
    // fprintf(output, "error state\n");
  }
  return 0;
}

void read_num(void) {
  int temp_num = 0;
  int sign = (c == '-') ? -1 : 1;
  if (c=='-') fscanf(input, "%c", &c);
  while ('0' <= c && c <= '9') {
    temp_num = temp_num * 10 + (int) (c - '0');
    // fprintf(output, "c=\"%c\"\n", c);
    fscanf(input, "%c", &c);
  }
  temp_num *= sign;
  a[i][j].number = temp_num;
  //fprintf(output, "temp_num=%d\n", temp_num);
}

void read_str(void) {
  int pos = 0;
  fscanf(input, "%c", &c);
  while (c != '\"') {
    a[i][j].string[pos] = c;
    fscanf(input, "%c", &c);
    pos++;
  }
  a[i][j].string[pos] = '\0';
  fscanf(input, "%c", &c);
}

void change_indices(void) {
  if (c == ' ') {
    while(c == ' ') {
      fscanf(input, "%c", &c);
      // fprintf(output, "$");
    }
  }
  if (c == ';') {
    j++;
  }
  else if (c == '\n') {
    m = j + 1;
    i++;
    j = 0;
  }
  // fprintf(output, "c=\"%c\"\n", c);

}



int program(void) {
  int skip_spaces_result = skip_spaces();
  // fprintf(output, "skip_spaces_result=%d\n", skip_spaces_result);

  if (skip_spaces_result == -1)
    return -1;

  state_type state = set_state();
      // fprintf(output, "c=\"%c\"\n", c);
  // fprintf(output, "state=%d\n", state);
  switch (state) {
    case reading_str:
      a[i][j].type = string;
      read_str();
      break;

    case reading_num:
      a[i][j].type = number;
      read_num();
      break;
    default:
      break;
  }

  change_indices();
  return 1;
}

void printing(void) {
  for (int ii = 0; ii < n; ii++) {
    for (int jj = 0; jj < m; jj++) {
      (a[ii][jj].type == string) ? fprintf(output, "\"%s\"", a[ii][jj].string) : fprintf(output, "%d", a[ii][jj].number);
      //fprintf(output, "%d\t", a[ii][jj].type);
      if (jj < m - 1) fprintf(output, ";");
    }
    fprintf(output, "\n");
  }
}

int is_first_bigger_than_second(elem x, elem y) {
  if (x.type == number) {
    return (x.number > y.number) ? 1 : 0;
  }
  else if (x.type == string) {
    return strcmp(x.string, y.string) > 0 ? 1 : 0;
  }
  return 0;
}

void init_with_k(void) {
  fscanf(input, "%d\n", &k);
  int x = 1;
  i = 0;
  j = 0;
  while(1) {
    x = program();
    if (x == -1)
      break;
  }
}

void init_without_k(void) {
  int x = 1;
  i = 0;
  j = 0;
  while(1) {
    x = program();
    if (x == -1)
      break;
  }
}

static void QuickSort (elem **a, int left, int right) {
  /* comp -- компаранд, i, j -- значения индексов */
  elem *comp, *tmp;
  int i, j;
  i = left; j = right;
  comp = a[(left + right)/2];
  do {
    while (is_first_bigger_than_second(comp[k], a[i][k]) && i < right)
      i++;
    while (is_first_bigger_than_second(a[j][k], comp[k]) && j > left)
      j--;
    if (i <= j) {
      tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++, j--;
    }
  } while (i <= j);
  if (left < j)
    QuickSort (a, left, j);
  if (i < right)
    QuickSort (a, i, right);
}

void Qsort (elem **a, int n) {
  QuickSort (a, 0, n - 1);
}

int main(void) {
  input = fopen("input.txt", "r");
  output = fopen("output.txt", "w");

  a = (elem**) malloc(100000 * sizeof(elem*));
  for (int i = 0; i < 100000; i++) {
    a[i] = (elem*) malloc(20 * sizeof(elem));
  }

  init_with_k();
  //printing();

  // fprintf(output, "%d %d\n", n, m);
  // qsort(a, n, sizeof(elem*), int (*) (const void *, const void *)) comp)
  /*
  for(int ii=1; ii < n; ii++)
	  for(int jj=ii; jj>0 && is_first_bigger_than_second(a[jj-1][k], a[jj][k]); jj--) { // пока j>0 и элемент j-1 > j, x-массив int
			elem *t;
      t = a[jj - 1];
      a[jj - 1] = a[jj];
      a[jj] = t;
  }
  */
  Qsort(a, n);
  printing();

  fclose(input);
  fclose(output);
}
