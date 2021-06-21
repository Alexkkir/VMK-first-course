#include <iostream>
using namespace  std;

struct node {
    node **child;

    node () {
        child = (node**) malloc(2 * sizeof(node*));
        child[0] = nullptr;
        child[1] = nullptr;
    }
};

struct bor {
    node *root = new node();
    int n_words = 0;
    int n_nodes = 1;

    void insert(int num) {
        node *p = root;
        int bit;

        for (int index = 0; index < 32; index++) {
            bit = get_bit(num, index);
            if (index == 31 && !p->child[bit])
                n_words++;
            if (!p->child[bit]) {
                p->child[bit] = new node();
                n_nodes++;
            }
            p = p->child[bit];
        }
    }

    static int get_bit(int num, int n) {
        return (num >> (31 - n)) & 1;
    }

    void erase (int num) {
        node *p = root;
        node *last_node = root;
        int dir_to_delete = (root->child[0]) ? 0 : 1;

        int index, bit, another;
        for (index = 0; index < 32; index++) {
            bit = get_bit (num, index);
            another = (bit + 1) % 2;
            if (p->child[another]) {
                last_node = p;
                dir_to_delete = bit;
            }
            if (p->child[bit]) {
                p = p->child[bit];
            }
            else {
                return;
            }
        }

        n_words--;
        delete_branch(last_node->child[dir_to_delete]);
        last_node->child[dir_to_delete] = nullptr;
    }
    void delete_branch(node *p) {
        if (!p) return;

        node *next = (p->child[0] != nullptr) ? p->child[0] : p->child[1];
        delete_branch(next);
        free(p);
        n_nodes--;
   }

   bool find(int num) {
        bool ok = true;
        node *p = root;
        int bit;
        for (int index = 0; index < 32; index++) {
            bit = get_bit(num, index);
            if (p->child[bit]) {
                p = p->child[bit];
            }
            else {
                ok = false;
            }
        }
        return ok;
    }

    int max_xor(int num) {
        if (!root || n_words == 0) return 0;

        node *p = root;
        int bit, another, ans = 0;
        for (int index = 0; index < 32; index++) {
            bit = get_bit(num, index);
            another = (bit + 1) % 2;
            bit = (p->child[another]) ? another : bit;
            ans = ans * 2 + bit;
            p = p->child[bit];
        }
        return ans;
    }

    void print() {
        print_(root, 0);
    }

    void print_(node *p, int level) {
        if (!p) return;
        print_(p->child[1], level + 1);
        for (int i = 0; i < level; i++) cout << "  ";
        cout << "*\n";
        print_(p->child[0], level + 1);
    }
};

int main() {
    bor bor;

    int n;
    cin >> n;

    node *median = NULL;
    int op, x;
    for (int i = 0; i < n; i++) {
        cin >> op;
        switch (op) {
            case 1:
                cin >> x;
                bor.insert(x);
                break;
            case 2:
                cin >> x;
                bor.erase(x);
                break;
            case 3:
                cin >> x;
                cout << bor.max_xor(x) << endl;
                break;
            case 4:
                bor.print();
                break;
            case 5:
                cin >> x;
                cout << bor.find(x) << endl;
            case 6:
                cin >> x;
                for (int i = 0; i < 32; i++) {
                    cout << bor.get_bit(x, i);
                }
                cout << endl;
            default:
                break;
        }
    }
}