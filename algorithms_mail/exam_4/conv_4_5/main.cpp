#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
//#include <ctime>
//#include <random>

using std::vector;
using std::pair;

struct shell {
    shell *prev;
    int verx;
    int very;
};

struct coords{
    int x, y;
};

bool comp1(std::pair<int,int> a, std::pair<int,int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}

bool comp2(std::pair<int,int> a, std::pair<int,int> b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

void mainfunc(shell* &end, std::vector<std::pair<int,int>> &arr, bool comp(std::pair<int,int>, std::pair<int,int>)) {
    int ax, ay, bx, by, tmpverx = 10001;

    std::sort(arr.begin(), arr.end(), comp);

    shell *p, *q;
    for (auto i : arr) {
        if (tmpverx == i.first) continue;
        tmpverx = i.first;
        p = new shell;
        p->verx = i.first;
        p->very = i.second;
        p->prev = end;
        end = p;
        while (p->prev && p->prev->prev) {
            ax = p->verx - p->prev->verx;
            ay = p->very - p->prev->very;
            bx = p->prev->verx - p->prev->prev->verx;
            by = p->prev->very - p->prev->prev->very;
            if (bx * ay - by * ax > 0) {
                q = p->prev;
                p->prev = p->prev->prev;
                delete q;
                //p = p->prev;
                continue;
            }
            break;
        }
    }
}

void getperim(shell *end) {
    shell *p;
    p = end->prev;
    int x, y, endx = end->verx, endy = end->very;
    double perim = 0;
    while (p) {
        x = end->verx - p->verx;
        y = end->very - p->very;
        perim += sqrt(x * x + y * y);
        delete end;
        end = p;
        p = p->prev;
    }
    x = end->verx - endx;
    y = end->very - endy;
    perim += sqrt(x * x + y * y);

    printf("%.2lf", perim);

    delete end;
}

void make_shell_array(shell *end, vector<coords> &ans) {
    shell *p;
    p = end->prev;
    while (p) {
        ans.push_back({end->verx, end->very});
        delete end;
        end = p;
        p = p->prev;
    }
    ans.push_back({end->verx, end->very});
    ans.push_back({ans[0].x, ans[0].y});
    delete end;
}

void calc_perim(vector<coords> &shell) {
    double perim = 0;
    for (int i = 0; i < shell.size() - 1; i++) {
        coords v, u;
        v = shell[i];
        u = shell[i + 1];

        int x, y;
        x = v.x - u.x;
        y = v.y - u.y;

        perim += sqrt(x * x + y * y);
    }

    printf("%.2lf", perim);
}

int main() {
    /*clock_t start, stop;
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<int> uid(-10000, 10000);*/

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> arr(n);
    for (auto &i:arr) {
        std::cin >> i.first >> i.second;
        //i.first=uid(gen);
        //i.second=uid(gen);
    }

    //start = clock();
    shell *end = nullptr;

    mainfunc(end, arr, comp1);

    mainfunc(end, arr, comp2);

    vector<coords> shell;
    make_shell_array(end, shell);
    // important: shell[0] == shell[-1]
    calc_perim(shell);

    return 0;
}