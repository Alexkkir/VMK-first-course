#include <stdlib.h>

int main(void) {
  FILE *inp = fopen("input.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  int a[5][2], n = 0;

  // while (!feof(inp))
	// 	if (fscanf(outp, "%d%d", &x1, &x2) > 0)
  //     n++;

  for (int i = 0; i < 5; i++)
    fscanf(inp, "%d", &a[i]);

  for (int i = 0; i < 5; i++)
    fprintf(outp, "%d ", a[i]);

  fclose(inp);
  fclose(outp);
}
