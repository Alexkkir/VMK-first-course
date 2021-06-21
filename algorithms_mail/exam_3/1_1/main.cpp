#include <iostream>

using namespace std;

long long f(string x) {
    if (x.empty()) return 0;

    long long n = x.size();

    if (x[0] < '3')
        return 0;
    else if (x[0] == '3') {
        if (n == 1)
            return 1;
        else
            return f(x.substr(1));
    }
    else if (x[0] < '7') {
        return (1 << (n - 1));
    }
    else if (x[0] == '7') {
        if (n == 1)
            return 2;
        else
            return (1 << (n - 1)) + f(x.substr(1));
    }
    else {
        return 1 << n;
    }
}


int main() {
    string x;
    cin >> x;

    long long n = x.size();
    long long ans, delta;

    ans = (1 << n) - 2;
    delta = f(x);
    ans += delta;

    cout << ans;

    return 0;
}
