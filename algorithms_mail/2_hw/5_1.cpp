#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
using namespace std;
using std::vector;

#define K 26
#define NMAX 10000000

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

struct vertex {
	int next[K];
	bool leaf;
};

void add_string (const string & s, int *sz_p, vector<vertex> *t) {
  int sz;
  sz = *sz_p;

	int v = 0;
	for (size_t i=0; i<s.length(); ++i) {
		char c = s[i]-'a'; // в зависимости от алфавита
		if ((*t)[v].next[c] == -1) {
      memset ((*t)[sz].next, -1, sizeof (*t)[sz].next);
			(*t)[v].next[c] = sz++;
		}
		v = (*t)[v].next[c];
	}
	(*t)[v].leaf = true;

  *sz_p = sz;
}

int main() {
  vector<vertex> t(NMAX);
    int sz;

  memset (t[0].next, 255, sizeof t[0].next);
  sz = 1;

  string line, sub;
  // cin >> line;
  line = "abracadabra";

  size_t n = line.size();
  for (size_t i = 0; i < n; i++) {
    sub = line.substr(i);
    add_string(sub, &sz, &t);
  }
  cout << sz - 1;
}
