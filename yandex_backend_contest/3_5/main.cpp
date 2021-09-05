#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

using std::unordered_map;
using std::unordered_multiset;
using std::multiset;
using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

#define ABS(x) x > 0 ? x : -x
#define MAX(a, b) a > b ? a : b

#define INF 1000000009
#define MAX_UNS 4294967295

struct cmp {
    bool operator() (int a, int b) const {
        return a > b;
    }
};

void fast_sort(unsigned *begin, unsigned *end) {
    size_t n = (size_t) (end - begin);

    const int deg = 8; // deg should be divider of 32
    const int base = 2 << deg;
    const int max_digit_ind = 32 / deg;
    unsigned mask = mask = 0b11111111;


    unsigned countDigit[base];
    unsigned *b = (unsigned*) malloc(n * sizeof(unsigned));

    unsigned count = 0, tmp, dig, x;
    for (size_t d_i = 0; d_i < max_digit_ind; d_i++) {
        for (unsigned j = 0; j < base; j++) {
            countDigit[j] = 0;
        }

        for (size_t j = 0; j < n; j++) {
            // dig = get_digit_2deg(*(begin + j), d_i, deg);
            dig = ((*(begin + j)) >> deg * d_i) & mask;
            countDigit[dig]++;
        }

        // for (int i = 0; i < base; i++) {
        //   printf("%d ", countDigit[i]);
        // }
        // printf("\n");

        count = 0;
        for (size_t j = 0; j < base; j++) {
            tmp = countDigit[j];
            countDigit[j] = count;
            count += tmp;
        }


        for (size_t j = 0; j < n; j++) {
            // dig = get_digit_2deg(*(begin + j), d_i, deg);
            dig = ((*(begin + j)) >> deg * d_i) & mask;
            b[countDigit[dig]] = *(begin + j);
            countDigit[dig]++;
        }

        // for (int i = 0; i < n; i++) printf("%d ", b[i]); printf("\n");
        memcpy(begin, b, 4 * n);
    }
    // free(digits);
    free(b);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    unsigned delta[n];
    unordered_map<int, int> fv;

    for (int pos = 0; pos < n; pos++) {
        auto elem = fv.find(a[pos]);
        if (elem != fv.end()) {
            printf("%d ", elem->second);
            continue;
        }

        for (int i = 0; i < n; i++) {
            delta[i] = abs(a[i] - a[pos]);
        }
        delta[pos] = INF;

        fast_sort(delta, delta + n);
        int sum = 0;

        for (int i = 0; i < k; i++) {
            sum += delta[i];
        }

        printf("%d ", sum);
        fv[a[pos]] = sum;
    }

    return 0;
}

