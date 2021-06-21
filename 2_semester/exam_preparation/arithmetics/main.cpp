#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;


void print_binary(int x, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        size_t move  = size - 1 - i;
        int bit = ((x) & (1 << move)) >> move;
        printf("%d", bit);

        count++;
        if (count % 4 == 0 && count != size) {
            printf("_");
        }
    }
    printf("\n");
}

#define MIN_INT (-2147483648)
#define MAX_INT 2147483647
#define MIN_SHORT (-32768)
#define MAX_SHORT 32767
#define CLOCKS_PER_SECOND

int main() {
    int i = 0x80000000;
    short s = 0x3;
    printf(" i: %d, \t s: %hd,  \t i < s:  %d\n", i, s, i < s);
    printf("-i: %d, \t-s: %hd,  \t-i > -s: %d\n", -i, -s, -s < -i);


    /*
    int x = 1E2;
    int bad = 0;

    long long total = (long long) MAX_INT * (long long) MAX_SHORT * 2;
    long long for_now = 0;

    auto start = high_resolution_clock::now();
    double frac_old = 0.0;

    for (int i = MIN_INT; i <= MAX_INT; i++) {
        for (short s = MIN_SHORT; s <= MAX_SHORT; s++) {
            int comp1, comp2;
            comp1 = (i < s);
            comp2 = (-i > -s);
            if (comp1 != comp2) {
                printf("bad i, s: %d %hd", i, s);
                bad++;
                break;
            }
        }
    }
    printf("is bad: %d", bad);
    return 0;
    */
}
