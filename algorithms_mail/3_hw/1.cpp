#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

int main() {
  vvll a(30, vll(2));

  for (int i = 0; i < 30; i++) {
    a[i][0] = i;
    a[i][1] = 0;
  }
  string s;
  cin >> s;

  int n = s.size();
  int ind;
  for (int i = 0; i < n; i++) {
    ind = (char) (s[i] - 'A');
    a[ind][1]++;
  }

  stable_sort(a.begin(), a.end(), [](vll x,vll y) {return (x[1]) > (y[1]);});

  for (int i = 0; i < 30 && a[i][1] != 0; i++) {
    printf("%c %d\n", (char) (a[i][0] + 'A'), a[i][1]);
  }
}
