#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define is_char(c) ('a' <= c && c <= 'z')
#define is_num(c) ('0' <= c && c <= '9')

char* collapse (char *s) {
  int pos_s = 0, pos_d = 0, dst_len = 1;
  char c = s[pos_s];
  char* dst = (char*) malloc(dst_len * sizeof(char)); // Один процент ??? и символ конца строки


  if (c == ' ') {
    pos_s++;
    c = s[pos_s];
  }

  while (is_char(c) || is_num(c) || c == ' ') {
    if (c == ' ') {
      pos_s++;
      c = s[pos_s];
    }
    if (is_char(c)) {
      // записываем процент
      dst = (char*) realloc (dst, (dst_len + 2) * sizeof(char));
      dst_len += 2;
      dst[pos_d] = '%';
      dst[pos_d + 1] = 's';
      pos_d += 2;
      // смещяем указатель
      while (is_char(c)) {
        pos_s++;
        c = s[pos_s];
      }
    }

    else if (is_num(c)) {
      dst = (char*) realloc (dst, (dst_len + 2) * sizeof(char));
      dst_len += 2;
      dst[pos_d] = '%';
      dst[pos_d + 1] = 'd';
      pos_d += 2;
      // смещяем указатель
      while (is_num(c)) {
        pos_s++;
        c = s[pos_s];
      }
    }
  }
  dst[pos_d] = '\0';
  return dst;
}

int main() {
  char *src = (char*) malloc(100 * sizeof(char));
  // scanf("%s", src);
  gets(src);
  printf("%s", collapse(src));
}
