#include <iostream>
#include <math.h>

int main()
{
    int x, y = 10, res;
    for (x = 1; x < 100; x++) {
        res = (int) ceil(((float) x) / ((float y)));
        printf("[%d\t/\t%d] =\t%d\n", x, y, res);
    }
}
