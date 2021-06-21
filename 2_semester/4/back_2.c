#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a, b;
  char op;
  scanf("%d %c %d", &a, &op, &b);
  switch (op) {
    case '+':
      printf("%d", a + b);
      break;
    case '-':
      printf("%d", a - b);
      break;
    case '*':
      printf("%d", a * b);
      break;
    case '/':
      printf("%d", a / b);
      break;
    default:
      break;
  }
  return 0;
}
