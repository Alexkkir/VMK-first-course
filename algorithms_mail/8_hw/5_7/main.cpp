#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::unordered_set;

#define  MAXN 2000

class bit_set {
public:
    using chunktype = unsigned long long;

//    bit_set(bit_set const &other) {
//        chunks = other.chunks;
//        setsize = other.setsize;
//        body = new chunktype[chunks];
//        for (int i = 0; i < chunks; i++) {
//            body[i] = other.body[i];
//        }
//    }

    const size_t CHUNKSIZE = 64;

    bit_set(size_t size) {  //    Конструктор
        chunks = (size + CHUNKSIZE - 1) / CHUNKSIZE;
        body = new chunktype[chunks];
        setsize = size;
        for (size_t i = 0; i < chunks; i++) {
            body[i] = 0;
        }
//        printf("size used: %zu bytes\n", chunks * sizeof(chunktype));
    }

    ~bit_set() {   /// Деструктор
        delete [] body;
    }

    void insert(size_t elem) {
        if (elem >= setsize) return;
        body[elem/CHUNKSIZE] |= chunktype(1) << (elem % CHUNKSIZE);
    }

    void erase(size_t elem) {
        if (elem >= setsize) return;
        body[elem/CHUNKSIZE] &= ~(chunktype(1) << (elem % CHUNKSIZE));
    }

    bool in(size_t elem) {
        if (elem >= setsize) return false;
        return (body[elem/CHUNKSIZE] >> (elem % CHUNKSIZE)) & 1;
    }

    void operator|= (bit_set const &other) const {
        for (int i = 0; i < chunks; i++) {
            body[i] |= other.body[i];
        }
    }

//    bit_set& operator= (bit_set&& other) {
//        // Guard self assignment
//        if (this == &other)
//            return *this; // delete[]/size=0 would also be ok
//
//        delete[] body;                               // release resource in *this
//        body = std::exchange(other.body, nullptr); // leave other in valid state
//        return *this;
//    }
public:
    chunktype *body;
    size_t setsize;
    size_t chunks;
};

void transitive_closure(bit_set **g, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
//            g[i] |= g[i].in(k) & g[k];
            if (g[i]->in(k)) {
                *g[i] |= *g[k];
            }
//            for (int j = 0; j < n; j++) {
//                g[i][j] = g[i][j] | (g[i][k] & g[k][j]);
//            }
        }
    }
}

void print_g(bit_set **g, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", g[i]->in(j));
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    bit_set **g = (bit_set**) malloc(n * sizeof(bit_set*));
    for (int i = 0; i < n; i++) {
        g[i] = new bit_set(n);
    }

    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while(scanf("%c", &c) && !(c == '0' || c == '1'));

            if (c == '1') {
                g[i]->insert(j);
            }
        }
    }

    transitive_closure(g, n);

    print_g(g, n);

    return 0;
}

