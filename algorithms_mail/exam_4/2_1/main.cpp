#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <string.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::string;

using std::cin;
using std::string;

int fun (string s) {
    int n = (int) s.length();
    vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = std::min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
        if (z[i] == n - i) {
            return n - z[i];
        }
    }
    return n;
}

int main() {
    string s;
    cin >> s;
    printf("%d", fun(s));
    return 0;
}
