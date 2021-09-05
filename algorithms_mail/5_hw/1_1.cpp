#include <iostream>
#include <map>
#include <string>
#include <string.h>

using namespace std;


typedef struct attempt{
    int score;
    int index;
    attempt() {
        score = -1;
        index = -1;
    }
} attempt;


typedef struct {
    char name[100 + 1];
    int score, index;
} person;


int comp(const void* x, const void *y) {
    return ((*(person *) x).score != (*(person *) y).score) ?
     ((*(person *) x).score < (*(person *) y).score) :
          ((*(person *) x).index > (*(person *) y).index);
}


int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    std::map<std::string, attempt> table;

    string s;
    int x, prev;
    for (int i = 0; i < n; i++) {
        cin >> s >> x;
        prev = table[s].score;

        if (x > prev) {
            table[s].score = x;
            table[s].index = i;
        }
    }

    person *arr = (person*) malloc ((m + 2) * sizeof(person));

    int i = 0, len;
    for (auto elem : table) {
        s = elem.first;
        len = s.size();
        s.copy(arr[i].name, len, 0);
        arr[i].name[len] = '\0';

        /*
        Если вместо 4-ёх строк выше написать
            arr[i].name = elem.first;
        и в структуре person описать поле name не как массив char-ов,
        а как объект string, то есть написать
            typedef struct {
                string name;
                int score, index;
            } person;
        то тогда в этом цикле происходит ошибка.
        Из-за чего? Ведь для объекта string определена операция присваивания.
        */

        arr[i].score = elem.second.score;
        arr[i].index = elem.second.index;
        i++;
    }

    qsort(arr, m, sizeof(person), comp);

    for (int i = 0; i < m; i++) {
        printf("%s\n", arr[i].name);
    }
}
