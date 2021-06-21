#include <iostream>
#include <vector>

enum cell{
    WALL,
    BLANK,
    DEADEND,
    START,
    FINISH,
    PASSED
};

struct coords {
    int x, y;

    inline bool operator== (coords another) const {
        return (x == another.x) && (y == another.y);
    }

    inline bool operator!= (coords another) const {
        return !((x == another.x) && (y == another.y));
    }
};

using namespace std;
using std::vector;

bool bad(vector<vector<cell>> &field, int x, int y) {
    return field[x][y] == WALL || field[x][y] == DEADEND;
}

bool blank_or_finish(vector<vector<cell>> &field, int x, int y) {
    return field[x][y] == BLANK || field[x][y] == FINISH;
}

bool is_angle_in_dir(vector<vector<cell>> &field, struct coords cell, int x, int y) {
    int i = cell.x, j = cell.y;
    return (!bad(field, i + x, j)) && (!bad(field, i + x, j + y)) && (!bad(field, i, j + y))
    && bad(field, i - x, j) && bad(field, i, j - y);
}

void mark_dead_path(vector<vector<cell>> &field, int x, int y) {
    if (field[x][y] != BLANK) return;

    int k = 0;
    bool is_angle = false;

    if (bad(field, x-1, y)) k++;
    if (bad(field, x+1, y)) k++;
    if (bad(field, x, y+1)) k++;
    if (bad(field, x, y-1)) k++;

    if (is_angle_in_dir(field, {x, y}, 1, 1)) is_angle = true;
    if (is_angle_in_dir(field, {x, y}, 1, -1)) is_angle = true;
    if (is_angle_in_dir(field, {x, y}, -1, 1) )is_angle = true;
    if (is_angle_in_dir(field, {x, y}, -1, -1)) is_angle = true;

    if (k == 4)
        field[x][y] = DEADEND;
    if (k == 3 || is_angle) {
        field[x][y] = DEADEND;
        mark_dead_path(field, x - 1, y);
        mark_dead_path(field, x + 1, y);
        mark_dead_path(field, x, y - 1);
        mark_dead_path(field, x, y + 1);
    }


}

void print(vector<vector<cell>> &field) {
    int n = field.size() - 2;
    int m = field[0].size() - 2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int elem = field[i][j];
            char c;
            switch(elem) {
                case WALL:
                    c = '0';
                    break;
                case BLANK:
                    c = '.';
                    break;
                case DEADEND:
                    c = 'X';
                    break;
                case START:
                    c = '@';
                    break;
                case FINISH:
                    c = '#';
                    break;
                case PASSED:
                    c = '*';
                    break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    coords start, finish;

    vector<vector<cell>> field(n + 2, vector<cell>(m + 2));
    for (int i = 0; i < n + 2; i++) {
        field[i][0] = WALL;
        field[i][n + 2 - 1] = WALL;
    }
    for (int i = 0; i < m + 2; i++) {
        field[0][i] = WALL;
        field[n + 2 - 1][i] = WALL;
    }

    char c;
    for (int i = 1; i < n + 2 - 1; i++) {
        for (int j = 1; j < m + 2 - 1; j++) {
            while (scanf("%c", &c) && (c == ' ' || c == '\n'));

            switch (c) {
                case '+':
                    field[i][j] = WALL;
                    break;
                case '.':
                    field[i][j] = BLANK;
                    break;
                case '@':
                    start = {i, j};
                    field[i][j] = START;
                    break;
                case '#':
                    finish = {i, j};
                    field[i][j] = FINISH;
                    break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mark_dead_path(field, i, j);

//            printf("%d %d\n", i, j);
//            print(field);
//            printf("\n");
        }
    }

    int length = 0;
    bool ok = true;
    coords tmp = start;
    while (ok && tmp != finish) {
        int i = tmp.x, j = tmp.y;
        field[i][j] = PASSED;

        if (field[i - 1][j] == BLANK || field[i - 1][j] == FINISH) {
            length++;
            tmp = {i - 1, j};
        }
        else if (field[i + 1][j] == BLANK || field[i + 1][j] == FINISH) {
            length++;
            tmp = {i + 1, j};
        }
        else if (field[i][j - 1] == BLANK || field[i][j - 1] == FINISH) {
            length++;
            tmp = {i, j - 1};
        }
        else if (field[i][j + 1] == BLANK || field[i][j + 1] == FINISH) {
            length++;
            tmp = {i, j + 1};
        }
        else {
            ok = false;
        }
    }

    /*
    int length = 0;
    bool ok = true;
    field[start.x][start.y] = PASSED;
    field[finish.x][finish.y] = BLANK;

    vector<coords> mark_passed;

    while (ok && field[finish.x][finish.y] != PASSED) {
        ok = false;
        length++;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // помечаем точки
                if (field[i][j] == PASSED) {
                    if (field[i + 1][j] == BLANK) {
                        ok = true;
                        mark_passed.push_back({i + 1, j});
                    }
                    if (field[i - 1][j] == BLANK) {
                        ok = true;
                        mark_passed.push_back({i - 1, j});
                    }
                    if (field[i][j - 1] == BLANK) {
                        ok = true;
                        mark_passed.push_back({i, j - 1});
                    }
                    if (field[i][j + 1] == BLANK) {
                        ok = true;
                        mark_passed.push_back({i, j + 1});
                    }
                }
            }
        }

        while(!mark_passed.empty()) {
            coords elem = mark_passed.back();
            field[elem.x][elem.y] = PASSED;
            mark_passed.pop_back();
        }
    }
    */
    printf("%d", ok ? length : -1);
    return 0;
}
