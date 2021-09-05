#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

void print(vector<vector<char>> &left, vector<vector<char>> &right) {
    for (int i = 0; i < left.size(); i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", left[i][j]);
            if (left[i][j] == 'X') {
                left[i][j] = '#';
            }
        }
        printf("_");
        for (int j = 0; j < 3; j++) {
            printf("%c", right[i][j]);
            if (right[i][j] == 'X') {
                right[i][j] = '#';
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d\n", &n);

    vector<vector<char>> left(n, vector<char>(3)), right(n, vector<char>(3));
    char t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            while (1) {
                scanf("%c", &t);
                if (t == '.' || t == '#')
                    break;
            }
            if (j < 3) {
                left[i][j] = t;
            } else {
                right[i][j - 3] = t;
            }
        }
    }

    int m;
    scanf("%d\n", &m);

    for (int input = 0; input < m; input++) {
        int k;
        string left_right, aisle_window;
        scanf("%d ", &k);
        cin >> left_right >> aisle_window;

        int choose[3];

        // определяем места, которые ищем
        if (left_right == "left") {
            if (aisle_window == "aisle") {
                for (int i = 0; i < k; i++) {
                    choose[i] = 3 - k + i;
                }
            } else {
                for (int i = 0; i < k; i++) {
                    choose[i] = i;
                }
            }
        } else {
            if (aisle_window == "aisle") {
                for (int i = 0; i < k; i++) {
                    choose[i] = i;
                }
            } else {
                for (int i = 0; i < k; i++) {
                    choose[i] = 3 - k + i;
                }
            }
        }

        // ищем места
        bool ok;
        if (left_right == "left") {
            for (int row = 0; row < n; row++) {
                ok = true;
                for (int i = 0; i < k; i++) {
                    int seat = choose[i];
                    if (left[row][seat] == '#') {
                        ok = false;
                        break;
                    }
                }
                if (ok == true) {
                    for (int i = 0; i < k; i++) {
                        int seat = choose[i];
                        left[row][seat] = 'X';
                    }

                    // места есть
                    printf("Passengers can take seats:");
                    for (int i = 0; i < k; i++) {
                        printf(" %d%c", row + 1, 'A' + choose[i]);
                    }
                    printf("\n");
                    print(left, right);
                    break;
                }
            }
        } else {
            for (int row = 0; row < n; row++) {
                ok = true;
                for (int i = 0; i < k; i++) {
                    int seat = choose[i];
                    if (right[row][seat] == '#') {
                        ok = false;
                        break;
                    }
                }
                if (ok == true) {
                    for (int i = 0; i < k; i++) {
                        int seat = choose[i];
                        right[row][seat] = 'X';
                    }

                    // места есть
                    printf("Passengers can take seats:");
                    for (int i = 0; i < k; i++) {
                        printf(" %d%c", row + 1, 'A' + choose[i] + 3);
                    }
                    printf("\n");
                    print(left, right);
                    break;
                }
            }
        }

        if (ok == false) {
            printf("Cannot fulfill passengers requirements\n");
        }
    }
    int x = 0;
    x++;
    return 0;
}
