#include <iostream>
#include <map>

void print_binary(const int *p, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        size_t move  = size - 1 - i;
        int bit = ((*p) & (1 << move)) >> move;
        printf("%d", bit);

        count++;
        if (count % 8 == 0 && count != size) {
            printf("_");
        }
    }
    printf("\n");
}

int main() {
    std::map<int, int> m;
    m[1] = 100;

    int x = 0;
    float f = 2;

    int *p = &x;
    f = *(float*)p;

    printf("x, f: %d %f\n", x, f);
    print_binary(p, 32);
    return 0;
}
