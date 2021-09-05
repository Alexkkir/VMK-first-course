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

void print_v(vector<vector<unsigned short>> const &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            printf("%d ", v[i][j] != INF ? v[i][j] : 0);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<vector<unsigned short>> board(n + 2, vector<unsigned short>(m + 2, 0));

    for (int i = 0; i < n + 2; i++) {
        board[i][0] = -1;
        board[i][m + 1] = -1;
    }

    for (int j = 0; j < m + 2; j++) {
        board[0][j] = -1;
        board[n + 1][j] = -1;
    }

    MyQueue q((n + 2) * (m + 2) + 1);

    for (int i = 0; i < k; i++) {
        unsigned short x, y;
        scanf("%hu%hu", &x, &y);

        x++;
        y++;

        board[x][y] = 1;
        q.push({x, y});
    }

    int max_dist = 0;

//    print_v(board);

    while(!q.empty()) {
        pair p = q.extract();

//        printf("x, y %d %d\n", p.x, p.y);

        auto v = (pair) {static_cast<unsigned short>(p.x - 1), p.y};
        if (board[v.x][v.y] == 0) {
            board[v.x][v.y] = (unsigned short) ((int) board[p.x][p.y] + 1);
            max_dist = MAX(max_dist, board[v.x][v.y]);
            q.push({v.x, v.y});
        }

        v = (pair) {static_cast<unsigned short>(p.x + 1), p.y};
        if (board[v.x][v.y] == 0) {
            board[v.x][v.y] = (unsigned short) ((int) board[p.x][p.y] + 1);
            max_dist = MAX(max_dist, board[v.x][v.y]);
            q.push({v.x, v.y});
        }

        v = (pair) {p.x, static_cast<unsigned short>(p.y - 1)};
        if (board[v.x][v.y] == 0) {
            board[v.x][v.y] = (unsigned short) ((int) board[p.x][p.y] + 1);
            max_dist = MAX(max_dist, board[v.x][v.y]);
            q.push({v.x, v.y});
        }

        v = (pair) {p.x, static_cast<unsigned short>(p.y + 1)};
        if (board[v.x][v.y] == 0) {
            board[v.x][v.y] = (unsigned short) ((int) board[p.x][p.y] + 1);
            max_dist = MAX(max_dist, board[v.x][v.y]);
            q.push({v.x, v.y});
        }

//        print_v(board);
    }

    printf("%d", max_dist - 1);
}