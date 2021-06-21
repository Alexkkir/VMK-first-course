#include <iostream>
#include <set>
#include <ctime>
#include <vector>

using std::vector;
using namespace  std;

typedef unsigned num_type;

struct node {
    node **child;
    bool flag = false;

    node () {
        child = (node**) malloc(2 * sizeof(node*));
        child[0] = nullptr;
        child[1] = nullptr;
    }
};

struct digit_bor {
    node *root;
    int n_words = 0;
    int n_nodes = 1;

    digit_bor() {
        root = fun(15);
    }

    node* fun(int lvl) {
        if (lvl > 0) {
            node *p = new node();
            p->child[0] = fun(lvl - 1);
            p->child[1] = fun(lvl - 1);
            return p;
        }
        else {
            return nullptr;
        }
    }

    void insert(num_type num) {

    }

    static num_type get_bit(num_type num, int n) {
        return (num >> (31 - (num_type) n)) & 1;
    }

    void erase (num_type num) {

    }

    num_type max_xor(num_type num) const {

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
    digit_bor bor;

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

            case 6:
                scanf("%u", &x);
                for (int index = 0; index < 32; index++) {
                    cout << digit_bor::get_bit(x, index);
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

num_type pure_max_xor(set<num_type> const &nums, num_type x) {
num_type max = 0, ret;
for (auto elem : nums) {
if ((elem ^ x) > max) {
max = (elem ^ x);
ret = elem;
}
}
return ret;
}

void print_set(set<num_type> nums) {
    printf("Nums array:\n");
    for (auto q : nums) printf("%u ", q);
    printf("\n");
}

num_type get_rand() {
    return ((num_type) rand() * rand() * rand()) % (4294967295 / 2) + 4294967295 / 2;
}

void single_test(int n, int &tests, int &errors) {
    set<num_type> nums;
    digit_bor bor;
    num_type my_ans, corr_ans;
    num_type x;
    for (int i = 0; i < n; i++) {
        x = get_rand();
        nums.insert(x);
    }

    n = nums.size();

    for (auto q : nums) {
        bor.insert(q);
    }

    //print_set(nums);
    for (int i = 0; i < n; i++) {

        // вычисления
        tests++;
        x = get_rand();
        my_ans = bor.max_xor(x);
        corr_ans = pure_max_xor(nums, x);

        // обработка
        if (my_ans == corr_ans) {
//            printf("+\t");
        }
        else {
//            printf("-\t");
            errors++;
        }
//        printf("x, my, corr %u %u %u\n", x, my_ans, corr_ans);
//        printf("bor_size %d\n", bor.n_words);

        // очистка
        x = *nums.begin();
        nums.erase(x);
        bor.erase(x);
    }
}

void testing() {
    std::srand(std::time(nullptr));
    int tests = 0, errors = 0;
    int n = 10001;
    for (int i = 0; i < 1; i++) {
        single_test(n,tests, errors);
    }
    printf("tests, errors %d %d", tests, errors);
}

int main() {
//    console();
//    testing();
    digit_bor b;
    cout << "here" << endl;
    b.print();
}