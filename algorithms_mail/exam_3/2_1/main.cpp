#include <iostream>
#include <vector>

using std::vector;

enum cell{
    WALL,
    BLANK,
    START,
    FINISH,
};

struct coords {
    long long x, y;

    inline bool operator== (coords another) const {
        return (x == another.x) && (y == another.y);
    }

    inline bool operator!= (coords another) const {
        return !((x == another.x) && (y == another.y));
    }
};

void set_one(long long &x) {
    x = (x != -1) ? 1 : -1;
}

long long not_wall(long long x) {
    return x != -1 ? x : 0;
}

void print(vector<vector<long long>> &field) {
    long long n = field.size() - 2;
    long long m = field[0].size() - 2;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            long long elem = field[i][j];
            char c;
            switch(elem) {
                case -1:
                    printf("0 ");
                    break;
                default:
                    printf("%d ", elem);
                    break;
            }
        }
        printf("\n");
    }
}

int main() {
    long long n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);

    coords start, finish;

    vector<vector<long long>> field(n + 2, vector<long long>(m + 2));
    for (long long i = 0; i < n + 2; i++) {
        field[i][0] = -1;
        field[i][n + 2 - 1] = -1;
    }
    for (long long i = 0; i < m + 2; i++) {
        field[0][i] = -1;
        field[n + 2 - 1][i] = -1;
    }

    char c;
    for (long long i = 1; i < n + 2 - 1; i++) {
        for (long long j = 1; j < m + 2 - 1; j++) {
            while (scanf("%c", &c) && (c == ' ' || c == '\n'));

            switch (c) {
                case '+':
                    field[i][j] = -1;
                    break;
                case '.':
                    field[i][j] = 0;
                    break;
                case '@':
                    start = {i, j};
                    field[i][j] = 0;
                    break;
                case '#':
                    finish = {i, j};
                    field[i][j] = 0;
                    break;
            }
        }
    }

    vector<vector<long long>> next = field;

    set_one(field[start.x + 1][start.y]);
    set_one(field[start.x - 1][start.y]);
    set_one(field[start.x][start.y - 1]);
    set_one(field[start.x][start.y + 1]);

    for (long long ep = 1; ep < k; ep++) {
        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= m; j++) {
                if (next[i][j] != -1) {
                    next[i][j] =
                            not_wall(field[i - 1][j]) +
                            not_wall(field[i + 1][j]) +
                            not_wall(field[i][j - 1]) +
                            not_wall(field[i][j + 1]);
                }
            }
        }
//        print(next);
//        printf("\n");
        field = next;
    }

    printf("%lld", field[finish.x][finish.y]);
    return 0;
}
