#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>    // std::reverse

using namespace std;

typedef struct tnode {
    string str;
    int R;
    int is_str;
    int n_childs;
    struct tnode *childs[10000];

    tnode () {
        n_childs = 0;
        for (int i = 0; i < 10000; i++) {
            childs[i] = NULL;
        }
    }
} node;

tnode *build(tnode *tree, string line, int left, int right) {
    //cout << endl << "left: " << left << "  right: " << right << endl;
    if (line[left + 1] != '(') {
        left++;

        char check_r = line[right];
        int is_r = ((check_r == 'R') ? 1 : 0);

        if (is_r == 1) {
            right--;
        }
        right--;

        //cout << "branch 1  " << left << " " << right << "\t" << line.substr(left, right + 1 - left) << endl;

        tnode *p = new tnode();
        p->str = line.substr(left, right + 1 - left);
        p->R = is_r;
        p->is_str = 1;
        return p;
    }
    else {
        left++;
        char check_r = line[right];
        int is_r = (check_r == 'R') ? 1 : 0;

        if (is_r == 1) {
            right--;
        }
        right--;

        //cout << "branch 2  " << left << " " << right << "\t" << line.substr(left, right + 1 - left) << endl;

        tnode *p = new tnode();
        p->R = is_r;
        p->is_str = 0;

        int flag_cont = 1;
        int j = left;
        int j_prev = left;
        while(flag_cont == 1 && j < right) {
            //cout << "\tj_prev " << j_prev << "  j " << j << "  [j]: " << line[j] << endl;

            int countt = 0;
            if (line[j] == '(') countt++;
            else {
                flag_cont = 0;
            }
            j++;
            while (countt != 0) {
                if (line[j] == '(') countt++;
                if (line[j] == ')') countt--;
                j++;
            }
            if (line[j] == 'R') j++;
            //else if (line[j] == ')') {j--;}

            //cout << "j_prev " << j_prev << "  j " << j << "  [j]: " << line[j] << endl;
            p->childs[p->n_childs] = build(tree, line, j_prev, j - 1);
            p->n_childs++;
            j_prev = j + 1;
            j++;
        }
        return p;
    }
}

void rotated_print(tnode* p, int n_level){
    if (!p) return;
    for ( int i = 0; i < n_level; i++, cout << "\t" );
    cout << p->R << " " << endl;
    for (int i = 0; i < p->n_childs; i++) {
        rotated_print(p->childs[i], n_level + 1);
    }
}

void norm(tnode *tree) {
    if (!tree) return;
    if (tree->is_str == 1) {
        return;
    }

    tnode *temp;
    int n = tree->n_childs;
    if (tree->R == 1) {
        for (int i = 0; i < n / 2; i++) {
            swap(tree->childs[i], tree->childs[n - i - 1]);
        }
    }

    for (int i = 0; i < n; i++) {
        tree->childs[i]->R ^= tree->R;
        norm(tree->childs[i]);
    }
    tree->R = 0;
}

void ans_print(tnode *p) {
    if (!p) return;
    if (p->is_str == 1) {
        string str = p->str;
        if (p->R == 1) {
            reverse(str.begin(), str.end());
        }
        cout << str;
    }
    int n = p->n_childs;
    for (int i = 0; i < n; i++) {
        ans_print(p->childs[i]);
    }
}

int main(void) {
    tnode* tree = NULL;

//    string line = "((ab)R,(ab)R,((ab)R,(ab)R)R,((ab)R,(ab)R,((ab)R,(ab)R)R)R,(((ab)R,(ab)R,((ab)R,(ab)R)R)R)R)R";
//    string line = "((ab),((ab),(ab))R,((ab),(ab)))";
    string line;
    cin >> line;
    tree = build(tree, line, 0, line.size() - 1);
    //cout << "Builded" << endl;

    //rotated_print(tree, 0);
    norm(tree);
    //rotated_print(tree, 0);
    ans_print(tree);
    return 0;
}