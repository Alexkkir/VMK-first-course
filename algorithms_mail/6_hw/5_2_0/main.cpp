#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::unordered_set;
using std::unordered_map;

#define MAX(a, b) a > b ? a : b
const unsigned long long p = 5;
const char zero = 'A';

vector<unsigned long long> ptab;
vector<unsigned long long> htab;

unsigned long long hashing(unsigned long long left, unsigned long long right) {
    if (left == 0)
        return htab[right];
    else {
        return (htab[right] - htab[left - 1]) / ptab[left];
    }
}

int main() {
    string s;
    cin >> s;

    unsigned long long n = s.size();

    ptab.assign(n, 0);
    ptab[0] = 1;
    for (unsigned long long i = 1; i < n; i++) {
        ptab[i] = ptab[i - 1] * p;
    }

    htab.assign(n, 0);
    htab[0] = s[0] - zero + 1;
    for (unsigned long long i = 1; i < n; i++) {
        htab[i] = htab[i - 1] + ((unsigned long long) s[i] - (unsigned long long) zero + 1) * ptab[i];
    }


    vector<unsigned long long> hashes(n);
    int ans = 0;
    for (unsigned long long len = 1; len <= n; len++) {
        // substrings with length = "len"
        for (unsigned long long pos = 0; pos < n + 1 - len; pos++) {
            hashes[pos] = hashing(pos, pos + len - 1);
        }

        int max_count = 0;
        for (unsigned long long i = 0; i < n + 1 - len; i++) {
            if (hashes[i] == -1) continue;

            int count = 1;

            for (int j = i + 1; j < n + 1 - len; j++) {
                if (hashes[j] == hashes[i]) {
                    int same = true;
                    for (int delta = 0; delta < len; delta++) {
                        if (s[i + delta] != s[j + delta]) {
                            same = false;
                            break;
                        }
                    }

                    if (same == true) {
                        count++;
                        hashes[j] = -1;
                    }
                }
            }

            hashes[i] = -1;
            max_count = MAX(max_count, count);
        }
        printf("max count: %d\n", max_count);

        ans = MAX(ans, max_count * len);
    }

    printf("%d", ans);

    return 0;
}