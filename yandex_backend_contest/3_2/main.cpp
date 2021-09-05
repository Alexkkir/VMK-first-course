#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

using std::unordered_multiset;
using std::multiset;
using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

#define ABS(x) x > 0 ? x : -x
#define MAX(a, b) a > b ? a : b

const int INF = 1000000009;

struct cmp {
    bool operator() (int a, int b) const {
        return a > b;
    }
};

struct MinElems {
    unordered_multiset<int> body;
    int size;

    MinElems(int n) {
        size = n;
    }

    void insert(int x) {

        if (body.size() < size) {
            body.insert(x);
            return;
        }

        int max = MinElems::max();
        auto max_it = body.find(max);
        if (x < *max_it) { // есть смысл вставить
            body.erase(max_it);
            body.insert(x);
        }
    }

    int sum() {
        int sum = 0;
        for (auto elem : body) {
            sum += elem;
        }
        return sum;
    }

    int max() {
        int max = 0;
        for (auto elem : body) {
            max = MAX(max, elem);
        }
        return max;
    }
};

int main_() {
    unordered_multiset<int> set = {1, 10, 100000, 100000000};
    for (auto q : set) {
        printf("%d ", q);
    }
    auto f = set.begin();
    printf("%d", *f);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int delta[n];
    for (int pos = 0; pos < n; pos++) {
        MinElems help(k);
        for (int i = 0; i < n; i++) {
            delta[i] = abs(a[pos] - a[i]);
        }
        delta[pos] = INF;

        for (int i = 0; i < n; i++) {
            help.insert(delta[i]);
        }

        printf("%d ", help.sum());
    }

    return 0;
}
