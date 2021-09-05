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
        ���� ������ 4-�� ����� ���� ��������
            arr[i].name = elem.first;
        � � ��������� person ������� ���� name �� ��� ������ char-��,
        � ��� ������ string, �� ���� ��������
            typedef struct {
                string name;
                int score, index;
            } person;
        �� ����� � ���� ����� ���������� ������.
        ��-�� ����? ���� ��� ������� string ���������� �������� ������������.
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
