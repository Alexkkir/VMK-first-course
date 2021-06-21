#include <assert.h>
#include <stdio.h>

class myset {
public:
    using chunktype = unsigned long long;
    const size_t CHUNKSIZE = 64;
    myset(size_t size) {  //    Конструктор
        chunks = (size + CHUNKSIZE - 1) / CHUNKSIZE;
        body = new chunktype[chunks];
        setsize = size;
        for (size_t i = 0; i < chunks; i++) {
            body[i] = 0;
        }
        printf("size used: %zu bytes\n", chunks * sizeof(chunktype));
    }

    ~myset() {   /// Деструктор
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
private:
    chunktype *body;
    size_t setsize;
    size_t chunks;
};



int main() {
    myset s1(1000); // create в абстракции и конструктор в C++.
    for (int i = 0; i < 10; i++) {
        s1.insert(i * i);
    }
    assert(s1.in(64));  // Проверка предиката
    s1.erase(64);
    assert(!s1.in(64)); // Ещё одна
}
