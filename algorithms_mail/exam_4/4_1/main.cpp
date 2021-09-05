#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::map;
using std::set;

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define MIN_3(a, b, c) MIN(a, MIN(b, c))
#define INF 1000000000

struct pair{
    unsigned short x, y;
};

struct MyQueue {
    pair *body;
    int first = 0, last = 0, bodysize;

    MyQueue(int n) {
        body = (pair*) malloc (n * sizeof(pair));
        bodysize = n;
    }

    ~MyQueue() {
        free(body);
    }

    void push(pair elem) {
        body[last++] = elem;

    }

    pair extract() {
        return (first < last) ? body[first++] : (pair) {0, 0};
    }

    void print() {
        for (int i = first; i < last; i++) {
            printf("%d %d; ", body[i].x, body[i].y);
        }
        printf("\n");
    }

    pair front() {
        return body[first];
    }

    int empty() {
        return first < last ? 0 : 1;
    }
};

void print_v(vector<vector<short>> const &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            printf("%d ", v[i][j] != INF ? v[i][j] : 0);
        }
        printf("\n");
    }
    printf("\n");
}

inline void enqueue (int *qi, short x, short y) {
    *qi = (((int) x) << 16 | (int) y);
}

inline void dequeue (int *qi, short &x, short &y) {
    x = short ((*qi) >> 16);
    y = short ((*qi) & 0x0000ffff);
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<vector<short>> board(n + 2, vector<short>(m + 2, 0));

    for (int i = 0; i < n + 2; i++) {
        board[i][0] = -1;
        board[i][m + 1] = -1;
    }

    for (int j = 0; j < m + 2; j++) {
        board[0][j] = -1;
        board[n + 1][j] = -1;
    }

//    MyQueue q((n + 2) * (m + 2) + 1);
    int *q = new int [(n + 2) * (m + 2) + 1];
    int *qf = q, *ql = q;

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        x++;
        y++;

        board[x][y] = 1;
//        q.push({x, y});
        *ql++ = (x << 16 | y);
    }

    int max_dist = 0;


    print_v(board);
    int u;
    short x, y;
    short v_x, v_y;
    while(qf != ql) {
//        pair p = q.extract();
        u = *qf++;
        x = ((short) u) >> 16;
        y = ((short) u) & 0x0000ffff;
        
        v_x = x - 1, v_y = y;
        if (board[v_x][v_y] == 0) {
            board[v_x][v_y] = (unsigned short) ((int) board[x][y] + 1);
            max_dist = MAX(max_dist, board[v_x][v_y]);
            *ql++ = (((int) v_x) << 16 | (int) v_y);
        }

        v_x = x + 1, v_y = y;
        if (board[v_x][v_y] == 0) {
            board[v_x][v_y] = (unsigned short) ((int) board[x][y] + 1);
            max_dist = MAX(max_dist, board[v_x][v_y]);
            *ql++ = (((int) v_x) << 16 | (int) v_y);
        }

        v_x = x, v_y = y - 1;
        if (board[v_x][v_y] == 0) {
            board[v_x][v_y] = (unsigned short) ((int) board[x][y] + 1);
            max_dist = MAX(max_dist, board[v_x][v_y]);
            *ql++ = (((int) v_x) << 16 | (int) v_y);
        }

        v_x = x, v_y = y + 1;
        if (board[v_x][v_y] == 0) {
            board[v_x][v_y] = (unsigned short) ((int) board[x][y] + 1);
            max_dist = MAX(max_dist, board[v_x][v_y]);
            *ql++ = (((int) v_x) << 16 | (int) v_y);
        }
//        print_v(board);
    }

    printf("%d", max_dist - 1);
}