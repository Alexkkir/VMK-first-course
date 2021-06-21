#include <iostream>
#include <vector>

using namespace std;
using std::vector;

class bit_set { // code from first seminar
public:
    using chunktype = unsigned long long;

    const size_t CHUNKSIZE = 64;

    bit_set(size_t size) {
        chunks = (size + CHUNKSIZE - 1) / CHUNKSIZE;
        body = new chunktype[chunks];
        setsize = size;
        for (size_t i = 0; i < chunks; i++) {
            body[i] = 0;
        }
    }

    ~bit_set() {
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

    void operator|= (bit_set const &other) const { // It is used if algorithm
        for (int i = 0; i < chunks; i++) {
            body[i] |= other.body[i];
        }
    }

public:
    chunktype *body;
    size_t setsize;
    size_t chunks;
};

void transitive_closure(vector<bit_set> &g) {
    int n = g.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (g[i].in(k)) {
                g[i] |= g[k];
            }
//            This is more effective form of this code:
//            for (int j = 0; j < n; j++) {
//                g[i][j] = g[i][j] | (g[i][k] & g[k][j]);
//            }
        }
    }
}

void print_g(vector<bit_set> &g){
    // Just printing
    int n = g.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", g[i].in(j));
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    vector<bit_set> g; // vector of classes
    for (int i = 0; i < n; i++) {
        g.push_back(bit_set(n)); // we fill it using push_back
    }

    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while(scanf("%c", &c) && !(c == '0' || c == '1'));

            if (c == '1') {
                g[i].insert(j); // filling graph
            }
        }
    }

    transitive_closure(g);

    print_g(g);

    return 0;
}

