#include <iostream>
#include <set>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;
using std::set;
using std::advance;
using std::vector;

struct fast_median {
    multiset<int> nums;
    std::_Rb_tree_const_iterator<int> median;

    void insert(int x) {
        if (nums.empty()) {
            nums.insert(x);
            median = nums.begin();
        }
        else {
            int m = *median;
            int n = nums.size();

            nums.insert(x);
            if (x < m && n % 2 == 1)
                median--;
            else if (m <= x && n % 2 == 0)
                median++;
        }
    }

    void erase(int x) {
        if (nums.size() == 1 && *nums.begin() == x) {
            nums.clear();
        }
        else if (nums.find(x) != nums.end()){
            int m = *median;
            int n = nums.size();

            // will be node MEDIAN deleted?
            if (x == m) {
                if (n == 2) {
                    median++;
                    nums.extract(x);
                    return;
                }
                else {
                    auto t = median;
                    t--;
                    if ((*t) != m) {
                        if (n % 2 == 0) {
                            median++;
                        } else {
                            median--;
                        }
                        nums.extract(x);
                        return;
                    }
                }
            }

            // will be deleted node either from the left side, or from the right side
            nums.extract(x);
            if (x <= m && n % 2 == 0) {
                median++;
            }
            else if (m < x && n % 2 == 1) {
                median--;
            }
        }
    }

    int get_median() const {
        return *median;
    }

    void print() {
        for (auto p : nums) {
            cout << p << " ";
        }
        cout << endl;
    }
};

void console() {
    fast_median fm;

    int n;
    cin >> n;

    int op;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> op;
        switch (op) {
            case 0:
                cin >> x;
                fm.insert(x);

//                fm.print();
//                cout << fm.get_median() << endl;
                break;
            case 1:
                cin >> x;
                fm.erase(x);

//                fm.print();
//                cout << fm.get_median() << endl;
                break;
            case 2:
                cout << fm.get_median() << endl;
                break;
            case 3:
                fm.print();
                break;
        }

    }
}

/*
int get_rand() {
    return rand() % 10;
}

void check(vector<int> &arr, fast_median &fm, int &tests, int &errors) {
    cout << endl;
    tests++;
    sort(arr.begin(), arr.end(), [](int a, int b){return a < b;});
    int my = fm.get_median();
    int corr = arr[(arr.size() + 1) / 2 - 1];
    if (my != corr) {
        errors++;
    }

    if (1) {
        bool same_nums = true;
        int index = 0;
        for (auto p : fm.nums) {
            if (p != arr[index]) {
                same_nums = false;
            }
            index++;
        }
        cout << "same nums: " << same_nums << endl;

        cout << "Arr:\n";
        for (int i : arr) {
            cout << i << " ";
        }
        cout << endl;

        cout << "FM:\n";
        for (auto p : fm.nums) {
            cout << p << " ";
        }
        cout << endl;

        cout << "my corr " << my << " " << corr << endl;
    }
    cout << ((my == corr) ? "+" : "-") << endl << endl;
}

void testing() {
    std::srand(std::time(nullptr));
    int n = 10, k = 10;
    int tests = 0, errors = 0;

    vector<int> arr;
    fast_median fm;

    int x;
    for (int i = 0; i < n; i++) {
        x = get_rand();
        arr.push_back(x);
        fm.insert(x);

        check(arr, fm, tests, errors);
    }

    for (int i = 0; i < k; i++) {
        int op = get_rand() % 2;
        switch (op) {
            case 0:
                x = get_rand();
                printf("Insert: %d\n", x);
                arr.push_back(x);
                fm.insert(x);
                break;
            case 1:
                int index = get_rand() % arr.size();
                x = arr[index];
                printf("Erase: %d\n", x);
                arr.erase(arr.begin() + index);
                fm.erase(x);
                break;
        }

        check(arr, fm, tests, errors);
    }

    cout << "\ntests errors: " << tests << " " << errors << endl;
}

*/

int main() {
//    testing();
    console();
    return 0;
}
