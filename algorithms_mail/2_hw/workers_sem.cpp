#include <stdio.h>
#include <vector>
using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

struct bset {
    void set(size_t bit) {
        val |= (1ull << bit);
    }
    void clear(size_t bit) {
        val &= ~(1ull << bit);
    }
    bool in(size_t bit) {
        return (val >> bit) & 1;
    }
    size_t val = 0;
};

ll count = 0;
const ll BIG = 1'000'000'000'000;
ll solve(vvll const &map, size_t pos, bset mask, ll sum, ll &reached) {
    if (sum >= reached) return BIG;
    size_t N = map.size();
    if (pos == N) {
        if (sum < reached) {
            printf("!!! new reached=%lld\n", sum);
            reached = sum;
        }
        return sum;
    }
    count++;
    ll bestval = BIG;
    for (size_t i = 0; i < N; i++) {
        if (mask.in(i)) continue;
        mask.set(i);
        auto res = solve(map, pos+1, mask, sum + map[pos][i], reached);
        if (res < bestval) bestval = res;
        mask.clear(i);
    }
    return bestval;
}

int main() {
    size_t N;
    scanf("%zu", &N);
    vvll map(N, vll(N));    // [N][N];
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            scanf("%lld", &map[i][j]);
        }
    }
    bset mask;
    ll reached = BIG;
    ll result = solve(map, 0, mask, 0, reached);
    printf("result=%lld count=%lld\n", result, count);
}
