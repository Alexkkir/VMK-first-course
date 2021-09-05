#include <iostream>


int max(int a, int b) {
    // if else < > ==

#if 0
    шпилевой системное программирование
столяров введение в проффессию программиста

http://www.stolyarov.info/books
https://youtu.be/XQ9LgtsDg7w

    ____

    8 4 2 1

    0___
    8 4 2 1

    1___
    -8 4 2 1

    1111 = -1

    0110 = a
    0111 = b

    a1 =    a & 1000 = 0
   b1 = b & 1000 = 0

           a > b        a -b > 0        c = a - b > 0        c1 = 0
                   c1 = 1

           a > b    c1 = 0      a
           a < b    c1 = 1      b
           a = b    c1 = 0      a


   ans = c1 *

           int *p;
    *p = 1;
    
#endif
    int c = a - b;

    int len = sizeof(int) * 8;
    int c1 = c >> (len - 1);
    c1 = c1 & 1;

    return a * (1 - c1) + b * c1;
}

int main() {
    int *p = (int*) 0;
    *p = 1;
//    printf("%d\n%d\n%d\n%d",
//           max(1, 2),
//           max(2, 1),
//           max(-1, -2),
//           max(-2, 1));
//    return 0;
}
