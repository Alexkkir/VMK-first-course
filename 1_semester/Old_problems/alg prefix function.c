#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*
int knut_f(const char *s, int *p)
{
  int n = strlen(s) - 1;
  p[0] = 0;
  int t, len;
  for(int i = 1; i < n; i++)
  {
    if(s[i] == s[p[i - 1]])
    {
      p[i] = p[i - 1] + 1;
    }
    else
    {
      t = i - 1;
      len = p[t];
      while((len > 0) && (s[len] != s[i]))
      {
        t = p - 1;
        len = p[t];
      }
    }
    p[i] = len + 1;
  }
}
*/
/*
vector<int> prefix_function(string s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        // префикс функция точно не больше этого значения + 1
        int cur = p[i - 1];
        // уменьшаем cur значение, пока новый символ не сматчится
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        // здесь либо s[i] == s[cur], либо cur == 0
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}
*/

int main(void)
{
  int str_len = 80;
  char s[str_len];
  fgets(s, str_len, stdin);
  int n = strlen(s) - 1;
  int p[n];
  for(int i = 0; i < n; i++) p[i] = 0;

  p[0] = 0;
  int t, len;
  for(int i = 1; i < n; i++)
  {
    if(s[i] == s[p[i - 1]])
    {
      p[i] = p[i - 1] + 1;
    }
    else
    {
      t = i - 1;
      len = p[t];
      while((len > 0) && (s[len] != s[i]))
      {
        t = t - 1;
        len = p[t];
      }
    }
    p[i] = len + 1;
  }

  for(int i = 0; i < n; i++) printf("%d", p[i]);
}
