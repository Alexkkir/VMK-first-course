#include <iostream>
#include <vector>
#include <string>
#include <set>

using std::multiset;
using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

#define ABS(x) x > 0 ? x : -x


struct MinElems {
    multiset<int> body;
    int size;

    MinElems(int n) {
        size = n;
    }

    void insert(int x) {

        if (body.size() < size) {
            body.insert(x);
            return;
        }

        auto max_it = body.end()--;
        if (x < *max_it) { // есть смысл вставить
            body.erase(max_it, max_it++);
            body.insert(x);
        }
    }

    multiset<int> get() const {
        return body;
    }

    int sum() {
        int sum = 0;
        for (auto elem : body) {
            sum += elem;
        }
        return sum;
    }
};

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int pos = 0; pos < n; pos++) {
        MinElems help(k);
        for (int i = 0; i < n; i++) {
            if (i == pos)
                continue;

            int delta = a[pos] - a[i];
            help.insert(ABS(delta));
        }

        printf("%d ", help.sum());
    }

    return 0;
}
