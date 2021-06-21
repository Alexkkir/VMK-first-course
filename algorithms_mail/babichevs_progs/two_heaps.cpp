#include <stdio.h>

int main() {
    unsigned N;
    scanf("%u", &N);
    int W[25];
    long long total = 0;
    for (unsigned i = 0; i < N; i++) {
        scanf("%d", &W[i]);
        total += W[i];
    }
    long long min = 1e18;
    unsigned lim = 1 << N;
    for (unsigned u = 0; u < lim; u++) {
        // u - генератор 1-й кучи
        long long part = 0; // RAII resource allocation is initialisation
        for (unsigned x = 0, v = u; v != 0; x++, v>>=1) {
            // Если бит x в числе u установлен - камень в 1-й куче
            part += W[x] * (v & 1);
        }
        // part - вес первой кучи
        long long dist = total - part - part;
        if (dist < 0) dist = -dist; // abs
        if (dist < min) min = dist; // min
    }
    printf("%lld\n", min);
}
