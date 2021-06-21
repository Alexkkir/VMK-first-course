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

typedef struct {
    int x, y;
} cell_t;

struct MyComp {
    bool operator()(const cell_t c1, const cell_t c2) const
    {
        return (c1.x != c2.x) ? (c1.x < c2.x) : (c1.y < c2.y) ;
    }
};

void print_set(set<cell_t, MyComp>  board) {
    printf("\n");
    for (auto elem : board) {
        printf("%d %d\n", elem.x, elem.y);
    }
    printf("\n");
}

bool inside_of_field(cell_t  cell,  int n,  int m) {
    return (0 <= cell.x && cell.x < n) && (0 <= cell.y && cell.y < m);
}

int count_neighbours(set<cell_t, MyComp>  &board,  int n,  int m,  cell_t cell) {
    int neighbours = 0;
    int i, j;

    int x = cell.x, y = cell.y;
    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if ( (i != x || j != y) && board.find({i, j}) != board.end() ) {
                neighbours++;
            }
        }
    }
    return neighbours;
}


void make_iteration(set<cell_t, MyComp> &board, const int n, const int m, vector<cell_t> &dead, vector <cell_t> &borned) {
    int nghb;
    bool alive;
    int i, j;

    // looking on all alive cells
    for (auto cell : board) {
        const int x = cell.x, y = cell.y;

        // looking on cell's neighbours and cell itself
        for (i = x - 1; i <= x + 1; i++)
            for (j = y - 1; j <= y + 1; j++) {
                if (inside_of_field({i, j}, n, m)) {
                    nghb = count_neighbours(board, n, m,  {i, j});
                    alive = (board.find({i, j}) != board.end());

                    // we are finding out, which cells become dead, and which borns
                    // arrays DEAD and BORNED initiallly are empty. In the end we clear them
                    if (alive == 1 && !(nghb == 2 || nghb == 3)) {
                        dead.push_back({i, j});
                    }
                    else if (alive == 0 && nghb == 3) {
                        borned.push_back({i, j});
                    }
                }
            }
    }

    for (i = dead.size(); i > 0; i--) {
        board.erase(dead[i - 1]);
        dead.pop_back();
    }

    for (i = borned.size(); i > 0; i--) {
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