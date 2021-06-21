#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000
#define MAX(a, b) a > b ? a : b

typedef struct number
{
  long long* value;
  long long negative, len;
} number;

number num1, num2, result;
char operation;

void init_num(number* num)
{
  num->value = (long long*) calloc(SIZE, sizeof(long long));
  num->len = 0;
}

void mirror_digits(number* num)
{
  long long n = num->len / 2;
  long long temp;
  for(long long i = 0; i < n; i++)
  {
    temp = num->value[i];
    num->value[i] = num->value[num->len - 1 - i];
    num->value[num->len - 1 - i] = temp;
  }
}

long long first_bigger_that_second(number a, number b)
{
  if (a.len > b.len)
  {
    return 1;
  }
  if (a.len < b.len)
  {
    return 0;
  }
  for (long long i = a.len - 1; i >= 0; i--)
  {
    if (a.value[i] > b.value[i])
    {
      return 1;
    }
    if (a.value[i] < b.value[i])
    {
      return 0;
    }
  }
  return 0;
}

void init_calc(void)
{
  init_num(&num1);
  init_num(&num2);
  init_num(&result);
  char c;
  long long digits_of_num1 = 1;
  while(scanf("%c", &c))
  {
    if (c == '\n') break;

    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
      operation = c;
      digits_of_num1 = 0;
    }

    else if('0' <= c && c <= '9')
    {
      if (digits_of_num1 == 1)
      {
        num1.value[num1.len] = (long long)(c - '0');
        num1.len++;
      }
      else
      {
        num2.value[num2.len] = (long long)(c - '0');
        num2.len++;
      }
    }
  }
  mirror_digits(&num1);
  mirror_digits(&num2);
}

void print(number num)
{
  if (num.negative == 1)
  {
    printf("-");
  }
  for(long long i = 0; i < num.len; i++)
  {
    printf("%lld", num.value[num.len - 1 - i]);
  }
}


void calc_sum(void)
{
  long long n = MAX(num1.len, num2.len);
  for (long long i = 0; i < n; i++)
  {
    result.value[i] = num1.value[i] + num2.value[i];
  }
  for (long long i = 0; i < n; i++)
  {
    if (result.value[i] >= 10)
    {
      result.value[i + 1]++;
      result.value[i] -= 10;
    }
  }
  if (result.value[n] != 0)
  {
    result.len = n + 1;
  }
  else
  {
    result.len = n;
  }
}

void calc_subs(void)
{
  long long n = MAX(num1.len, num2.len);
  long long comparison = first_bigger_that_second(num1, num2);
  number a = comparison ? num1 : num2;
  number b = comparison ? num2 : num1;

  for (long long i = 0; i < n; i++)
  {
    result.value[i] = a.value[i] - b.value[i];
  }
  for (long long i = 0; i < n; i++)
  {
    if (result.value[i] < 0)
    {
      result.value[i + 1]--;
      result.value[i] += 10;
    }
  }
  if (result.value[n] != 0)
  {
    result.len = n + 1;
  }
  else
  {
    result.len = n;
  }
  if (comparison == 0)
  {
    result.negative = 1;
  }
  long long i;
  for (i = n - 1; i >= 0 && result.value[i] == 0; i--);
  result.len = i + 1;
  if (result.len == 0)
  {
    result.len = 1;
    result.negative = 0;
  }
}

void calc_mult(void)
{
  long long n = num1.len + num2.len;
  for(long long i = 0; i < n; i++)
  {
    for(long long j = 0; j <= i; j++)
    {
      //prlong longf("%lld %lld %lld\n", num1.value[j], num2.value[i - j], num1.value[j] * num2.value[j - i]);
      result.value[i] += num1.value[j] * num2.value[i - j];
    }
  }
  for(long long i = 0; i < n; i++)
  {
    if (result.value[i] >= 10)
    {
      result.value[i + 1] += result.value[i] / 10;
      result.value[i] %= 10;
    }
    //prlong longf("%lld\n", result.value[i]);
  }
  long long i;
  for (i = n - 1; i >= 0 && result.value[i] == 0; i--);
  result.len = i + 1;
  if (result.len == 0)
  {
    result.len = 1;
    result.negative = 0;
  }
}

void run_calc(void)
{
  if (operation == '+')
  {
    calc_sum();
  }

  if (operation == '-')
  {
    calc_subs();
  }

  if (operation == '*')
    calc_mult();
}

int main (void)
{
  init_calc();
  run_calc();
  print(result);
  free(num1.value);
  free(num2.value);
  free(result.value);
}
