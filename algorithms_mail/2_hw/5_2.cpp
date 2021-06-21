#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
using namespace std;
using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

#define max(a, b) (a > b) ? a : b


vector<int> z_function (string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

int z_function_max (string s) {
	int n = (int) s.length();
	vector<int> z = z_function(s);
  int max_el = 0;
  for (int i = 0; i < n; i++) {
    max_el = max(max_el, z[i]);
  }
  // printf("max_el: %d\n", max_el);
	return max_el;
}

int main() {
  string inp;
  cin >> inp;

  int n = inp.size();
  int ans = 0;
  string s;
  for (int i = 0; i <= n; i++) {
    s = inp.substr(0, i);
    reverse(s.begin(), s.end());
    // cout << s << endl;
    ans += i - z_function_max(s);
  }
  printf("%d", ans);
}
