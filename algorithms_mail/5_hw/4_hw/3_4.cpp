#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MIN_INT -2147483648

#define MIN(a, b) (a < b) ? a : b
#define MAX(a, b) (a > b) ? a : b

int sum_(int a, int b) {
    return a + b;
}
int xor_(int a, int b) {
    return (a ^ b);
}
int max_(int a, int b) {
    return (a > b) ? a : b;
}

struct segment_tree {
    int *t;
    int body_size;
    int actual_size;
    int last_level;
    int start_point;
    int n;
    int (*op) (int, int);
    int e;


    segment_tree(int len, int(*operation)(int, int)) {
        body_size = 4 * len;
        t = (int*) malloc (body_size * sizeof(int));
        n = len;

        op = xor_;
        e = 0;
        if (operation(1, 2) == 2) {
            op = max_;
            e = MIN_INT;
        } else {
            op = xor_;
            e = 0;
        }

        last_level = 0;
        start_point = 1;
        while (!(start_point / 2 < n && n <= start_point)) {
            last_level++;
            start_point *= 2;
        }
        actual_size = start_point * 2;
    }

    ~segment_tree() {
        delete t;
    }


    void build (int a[]) {
        int left = start_point, right = left * 2;
        for (int i = left; i < left + n; i++) {
            t[i] = a[i - left];
        }

        for (int i = left + n; i < right; i++) {
            t[i] = e;
        }
        left /= 2; right /= 2;

        while(left > 0) {
            for (int i = left; i < right; i++) {
                t[i] = op(t[2 * i], t[2 * i + 1]);
            }
            left /= 2; right /= 2;
        }
    }

    int calc_(int left, int right) {
        if (left == right) return t[left];
        if (left > right) return e;

        int res = e;
        if (left % 2 == 1) res = op(res, t[left++]);
        if (right % 2 == 0) res = op(res, t[right--]);
        res = op(res, calc_(left / 2, right / 2));
        return res;
    }

    int calc (int first, int last) {
        return calc_(start_point + first, start_point + last);
    }

    void update (int index, int new_val) {
        int pos = start_point + index;
        t[pos] = new_val;
        pos /= 2;

        while(pos > 0) {
            t[pos] = op(t[2 * pos], t[2 * pos + 1]);
            pos /= 2;
        }
    }

    void print(int index = 1, int spaces = 0) {
        if (index >= actual_size) return;
        print(index * 2 + 1, spaces + 1);

        for (int i = 0; i < spaces; i++) {
            printf("\t");
        }
        printf("%d\n", t[index]);
        print(index * 2, spaces + 1);
    }
};

int main() {
    int n, m;
	scanf("%d%d", &n, &m);

	int a[n];
	for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
	}

	segment_tree t_max = segment_tree(n, max_);
	t_max.build(a);

	segment_tree t_xor = segment_tree(n, xor_);
	t_xor.build(a);

	for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);

        int x, y;
        int pos, val;
        switch (op) {
            case 1:
                scanf("%d%d", &x, &y);
                printf("%d\n", t_xor.calc(x, y));
                break;
            case 2:
                scanf("%d%d", &x, &y);
                printf("%d\n", t_max.calc(x, y));
                break;
            case 3:
                scanf("%d%d", &pos, &val);
                t_xor.update(pos, val);
                t_max.update(pos, val);
                break;
        }
    }

    return 0;
}
