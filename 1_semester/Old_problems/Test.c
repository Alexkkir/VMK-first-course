/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int f(void)
{
    char symb;
    int n = 0;
    int p, q;    printf("+");

    scanf("%c", &symb);
    printf("+");
    if ((symb == '*') || (symb == '/') || (symb == '+') || (symb == '-'))
    {
        scanf("%c", &symb); // пропускаем пробел

        printf("+");
        p = f();
        printf("+");
        q = f();
        return p + q;
    }
    if ((symb >= '0') && (symb <= '9')) // считываем многозначное число
    {
        while ((symb >= '0') && (symb <= '9'))
        {
            n = 10 * n + (int)(symb);
        }
        return n;
    }
    if (symb == ' ')
    {
        f();
    }
    printf("+");
}

int main(void)
{
    int ans;
    ans = f();
    printf("%d", ans);
}
