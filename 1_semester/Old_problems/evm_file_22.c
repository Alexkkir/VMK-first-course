#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 10000

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strncpy(result, s1, strlen(s1) - 1);
    strcat(result, s2);
    return result;
}
/*
int min_cycle_shift(char *s, int len) {
  int i = 0, ans = 0;
  while (i < len/2) {
    ans = i;
    int k = i, j = i+1;
    while (j < len && s[k] <= s[j]) {
      if (s[k] < s[j])
        k = i;
      else
        ++k;
      ++j;
    }
    while (i<=k)
      i += j - k;
  }
  return ans + 1;
}

char* min_cyclic_shift_2 (char* s1) {
	char s = *concat(s1, s1);
	int n = strlen(s) - 1;
	int i=0, ans=0;
	while (i < n/2) {
		ans = i;
		int j=i+1, k=i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				++k;
			++j;
		}
		while (i <= k)  i += j - k;
	}
	return s.substr (ans, n/2);
}
*/
int main(void)
{
  /*
  char s[STR_SIZE];
  fgets(s, STR_SIZE, stdin);

  int n = strlen(s) - 1;

  char* ss = concat(s, s);
  char sss = *ss;
  puts(sss);
  */
  int *p;
  *p = 5;
  printf("%d", *p);
  int a;
  a = *p;
  printf("%d", a);
}
