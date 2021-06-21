#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1000009

char symbol(char *s, int i)
{
  int n = strlen(s) - 1;
  int j = i%n;
  return s[j];
}



int main(void)
{
  static char s[STR_SIZE];
  fgets(s, STR_SIZE, stdin);
  int n = strlen(s) - 1;

  int i_min = n - 1;


  for(int i = n - 1; i >= 0; i--)
  {
    if(symbol(s, i + 0) == '1')
    {
      continue;
    }
    if (symbol(s, i + 0) == '0' && symbol(s, i + n - 1) != '1') continue;

    int smaller = 1;
    for(int j = 0; j < n; j++)
    {
      if(symbol(s, i + j) < symbol(s, i_min + j))
      {
        break;
      }
      else if(symbol(s, i + j) > symbol(s, i_min + j))
      {
        smaller = 0;
        break;
      }
      //printf("%c %c\n", symbol(s, i + j), symbol(s, i_min + j));
    }
    if (smaller == 1)  i_min = i;
  }
  for(int i = 0; i < n; i++)
  {
    printf("%c", symbol(s, i_min + i));
  }
}
