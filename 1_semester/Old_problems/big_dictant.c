#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1000009

int main(void)
{
  char s[STR_SIZE];
  fgets(s, STR_SIZE, stdin);
  int n = strlen(s) - 1;
  //printf("%d\n", n);
  static int left[STR_SIZE][2] = {0}, right[STR_SIZE][2] = {0};

  left[0][0] = 0; left[0][1] = 0; right[n - 1][0] = 0; right[n - 1][1] = 0;
  for(int i = 1; i < n; i++)
  {
    if (s[i - 1] == 'A')
    {
      left[i][i % 2] = left[i - 1][i % 2] + 1;
      left[i][(i + 1) % 2] = left[i - 1][(i + 1) % 2];
      // printf("%d * \n", left[i][i % 2]);
    }
    else
    {
      left[i][0] = left[i - 1][0];
      left[i][1] = left[i - 1][1];
    }
  }
  for(int i = n - 2; i >= 0; i--)
  {
    if(s[i+1] == 'A')
    {
      right[i][i % 2] = right[i + 1][i % 2] + 1;
      right[i][(i + 1) % 2] = right[i + 1][(i + 1) % 2];
    }
    else
    {
      right[i][0] = right[i + 1][0];
      right[i][1] = right[i + 1][1];
    }
  }
  for(int i = 0; i < n; i++)
  {
    if(left[i][0] + right[i][1] == left[i][1] + right[i][0])
      printf("%d \n", i + 1);
  }
  /*
  for(int i = 0; i < n; i++) printf("% d", left[i][0]);
  printf("\n");
  for(int i = 0; i < n; i++) printf("% d", left[i][1]);
  printf("\n");
  for(int i = 0; i < n; i++) printf("% d", right[i][0]);
  printf("\n");
  for(int i = 0; i < n; i++) printf("% d", right[i][1]);
  printf("\n");
  */
}
