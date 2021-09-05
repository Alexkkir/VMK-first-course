#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using std::vector;
using std::multiset;
using std::unordered_multiset;
#include <chrono>
using namespace std::chrono;

int main() {
    vector<int> sizes = {10, 100, 200, 500, 1000, 2000, 5000, 10000};
    int n_tests = 1000;
    int n_subtests = 1000;

    printf("avl multiset:\n");
    for (auto n : sizes) {
        auto start = high_resolution_clock::now();
        for (int test = 0; test < n_tests; test++) {
            multiset<int> set;
            for (int i = 0; i < n; i++) {
                set.insert(rand());
            }
            for (int attempt = 0; attempt < n_subtests; attempt++) {
                set.find(rand());
            }
        }
        auto end = high_resolution_clock::now();
        double time = double ((duration_cast<nanoseconds>(end - start).count())) / (n_tests * n_subtests * 1000000000);
        printf("size: %d\ttime: %f\n", n, time);
    }

    printf("\n\nhastable multiset:\n");
    for (auto n : sizes) {
        auto start = high_resolution_clock::now();
        for (int test = 0; test < n_tests; test++) {
            unordered_multiset<int> set;
            for (int i = 0; i < n; i++) {
                set.insert(rand());
            }
            for (int attempt = 0; attempt < n_subtests; attempt++) {
                set.find(rand());
            }
        }
        auto end = high_resolution_clock::now();
        double time = double ((duration_cast<nanoseconds>(end - start).count())) / (n_tests * n_subtests * 1000000000);
        printf("size: %d\ttime: %f\n", n, time);
    }
    return 0;
}
