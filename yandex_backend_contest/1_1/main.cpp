#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        printf("0");
        return 0;
    }

    int first, prev, curr, last;
    bool ok;

    cin >> first;
    prev = first;
    for (int i = 1; i < n; i++) {
        cin >> curr;
        if (prev > curr) {
          printf("-1");
          return 0;
        }
        prev = curr;
    }

    last = curr;
    printf("%d", last - first);
    return 0;
}
