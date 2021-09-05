#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>

#include <set>
#include <vector>

using namespace std;
using std::set;
using std::vector;

struct cell_t{
    int x, y;
};

struct MyComp {
    bool operator()(const cell_t c1, const cell_t c2) const
    {
        return (c1.x != c2.x) ? (c1.x < c2.x) : (c1.y < c2.y) ;
    }
};


void print_set(set<cell_t, MyComp> board) {
    printf("\n");
    for (auto elem : board) {
        printf("%d %d\n", elem.x, elem.y);
    }
    printf("\n");
}

int count_neighbours(set<cell_t, MyComp> board, cell_t cell) {
    int neighbours = 0;
    int x = cell.x, y = cell.y;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if ( (i != x || j != y) && board.find({i, j}) != board.end() ) {
                neighbours++;
            }
        }
    }
    return neighbours;
}

bool inside_of_field(cell_t cell, int n, int m) {
    return (0 <= cell.x < n) && (0 <= cell.y < m);
}

void make_iteration(set<cell_t, MyComp> &board, int n, int m, vector<cell_t> &dead, vector <cell_t> &borned) {
    int nghb;
    bool alive;

    for (auto cell : board) {
        // look on all cells in sphere of current cell
        int x = cell.x, y = cell.y;

        for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++) {
                if (!inside_of_field({i, j}, n, m)) continue;

                nghb = count_neighbours(board, {i, j});
                bool alive = (board.find({i, j}) != board.end());

                // клетка зарождается, если у нее 3 соседа
                // клетка умирает, если у нее не 2 или 3 соседа
                if (alive == 1 && !(nghb == 2 || nghb == 3)) {
                    dead.push_back({i, j});
                }
                else if (alive == 0 && nghb == 3) {
                    borned.push_back({i, j});
                }
            }
    }

    for (int i = dead.size(); i > 0; i--) {
        board.erase(dead[i - 1]);
        dead.pop_back();
    }

    for (int i = borned.size(); i > 0; i--) {
        board.insert(borned[i - 1]);
        borned.pop_back();
    }

    dead.clear();
    borned.clear();
}

int main() {
    int n, m, num_epoches, alive;

    scanf("%d %d %d %d", &n, &m, &alive, &num_epoches);

    set<cell_t, MyComp> board;
    vector<cell_t> dead, borned;

    int x, y;
    for (int i = 0; i < alive; i++) {
        scanf("%d%d", &x, &y);
        board.insert({x, y});
    }

    //printf("===\n");

    for (int epoch = 0; epoch < num_epoches; epoch++) {
        make_iteration (board, n, m, dead, borned);
    }

    for (auto elem : board) {
        printf("%d %d\n", elem.x, elem.y);
    }
}
