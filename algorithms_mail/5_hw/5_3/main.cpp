#include <iostream>
#include <set>
#include <ctime>
#include <vector>

using std::vector;
using namespace  std;

typedef unsigned num_type;

struct node {
    node **child;

    node () {
        child = (node**) malloc(2 * sizeof(node*));
        child[0] = NULL;
        child[1] = NULL;
    }
};

node * new_node() {
    node *p = (node*) malloc(sizeof(node));
    p->child = (node**) malloc(2 * sizeof(node*));
    p->child[0] = NULL;
    p->child[1] = NULL;
    return p;
}

struct bor {
    node *root;
    int n_words = 0;
    int n_nodes = 1;

    bor () {
        root = new_node();
    };

    void insert(num_type num) {
        node *p = root;
        num_type bit;

        for (int index = 0; index < 32; index++) {
            bit = get_bit(num, index);
            if (index == 31 && !p->child[bit])
                n_words++;
            if (!p->child[bit]) {
                p->child[bit] = new_node();
                n_nodes++;
            }
            p = p->child[bit];
        }
    }

    static num_type get_bit(num_type num, int n) {
        return (num >> (31 - (num_type) n)) & 1;
    }

    void erase (num_type num) {
        node *p = root;
        node *last_node = root;
        num_type dir_to_delete; // = (root->child[0]) ? 0 : 1;

        int index;
        num_type bit, another;
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

        // such word exists in bor and should be deleted
        if (last_node == root) {
            dir_to_delete = (root->child[0]) ? 0 : 1;
//            last_node = root;
        }
//        delete_branch(last_node->child[dir_to_delete]);
        last_node->child[dir_to_delete] = NULL;
        n_words--;
    }

    void delete_branch(node *p) {
        if (!p) return;

        node *next = (p->child[0] != NULL) ? p->child[0] : p->child[1];
        delete_branch(next);
        delete p;
        n_nodes--;
    }

    bool find(num_type num) const {
        bool ok = true;
        node *p = root;
        num_type bit;
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

    num_type max_xor(num_type num) const {
        if (!root || n_words == 0) return 0;

        node *p = root;
        num_type bit, another, ans = 0;
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

void console() {
    bor bor;

    int n;
    cin >> n;

    int op;
    num_type x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%u", &x);
                bor.insert(x);
                break;
            case 2:
                scanf("%u", &x);
                bor.erase(x);
                break;
            case 3:
                scanf("%u", &x);
                cout << bor.max_xor(x) << endl;
                break;
            case 4:
                bor.print();
                break;
            case 5:
                scanf("%u", &x);
                cout << bor.find(x) << endl;
                break;
            case 6:
                scanf("%u", &x);
                for (int index = 0; index < 32; index++) {
                    cout << bor::get_bit(x, index);
                }
                cout << endl;
                break;
            case 7:
                cout << bor.n_words << endl;
            default:
                break;
        }
    }
}

int main() {
    console();
//    testing();
}