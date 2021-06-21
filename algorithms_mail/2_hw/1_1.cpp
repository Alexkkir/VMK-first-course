#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
using std::vector;

using ll = long long;
using vll = vector<ll>;

#define max(a, b) (a > b) ? a : b

int main() {
  // FILE *file = fopen("inp.txt", "r");

  size_t n; scanf("%zu", &n);
  vll starts, ends;

  size_t ind1, ind2;
  for (size_t i = 0; i < n; i++) {
    ll t1 = 0, t2 = 0, t3 = 0, s1 = 0, s2 = 0, s3 = 0;

    // fscanf(file, "%lld:%lld:%lld %lld:%lld:%lld", &t1, &t2, &t3, &s1, &s2, &s3);
    // ll t = t1 * 3600 + t2 * 60 + t3;
    // ll s = s1 * 3600 + s2 * 60 + s3;
    scanf("%lld:%lld %lld:%lld", &t1, &t2, &s1, &s2);
    ll t = t1 * 60 + t2;
    ll s = s1 * 60 + s2;

    starts.push_back(t);
    ends.push_back(s);
  }

  sort(starts.begin(), starts.end(), [](int a, int b) {return a < b;});
  sort(ends.begin(), ends.end(), [](int a, int b) {return a < b;});

  ind1 = 0; ind2 = 0;
  ll count = 0, max_count = 0;
  while(ind1 < n || ind2 < n) {
    if (ind1 < n && starts[ind1] <= ends[ind2]) {
      count++;
      ind1++;
    } else {
      count--;
      ind2++;
    }
    // printf("count %d\n", count);
    max_count = max(max_count, count);
  }

  printf("%lld", max_count);

}
