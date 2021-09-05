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
    int n;
	scanf("%d", &n);

	int a[n];
	for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
	}


    segment_tree *t_xor =  new segment_tree(n, xor_);
    segment_tree *t_max =  new segment_tree(n, max_);

    t_xor->build(a);

    for (int i = 0; i < 4 * n; i++) {
        printf("%d\n", t_max->t[i]);
    }

	printf("here");


    return 0;
}
