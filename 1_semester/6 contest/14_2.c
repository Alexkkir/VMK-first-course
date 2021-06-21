#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *input, *output;

int binary_scanf_2(void){
  int ans = 0, ans1 = 0, ans2 = 0;
  fread(&ans1, sizeof(char), 1, input);
  fread(&ans2, sizeof(char), 1, input);
  ans = (ans1<<8) + ans2;
  return ans;
}

int binary_scanf_4(void){
  int ans, ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;
  fread(&ans1, sizeof(char), 1, input);
  fread(&ans2, sizeof(char), 1, input);
  fread(&ans3, sizeof(char), 1, input);
  fread(&ans4, sizeof(char), 1, input);
  ans = (ans1 << 8 * 3) + (ans2 << 8 * 2) + (ans3 << 8) + ans4;
  return ans;
}

void binary_printf(long long x, int num_bytes){
  if (num_bytes > 1){
    binary_printf(x>>8, num_bytes - 1);
  }
  fwrite(&x, sizeof(char), 1, output);
}

int main(void) {
  input = fopen("matrix.in", "rb");
  output = fopen("trace.out", "wb");

  int n = binary_scanf_2();
  long long int tr = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x = binary_scanf_4();
      if (i == j) {
        tr += (long long) x;
      }
    }
  }

  binary_printf(tr, 8);

  fclose(input);
  fclose(output);
  return 0;
}
