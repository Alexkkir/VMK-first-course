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

int n;
int *a;

void build_ (int *t, int a[], int v, int tl, int tr, int(*op)(int, int)) {
	if (tl == tr) {
		t[v] = a[tl];
	}
	else {
		int tm = (tl + tr) / 2;
		build_ (t, a, v*2, tl, tm, op);
		build_ (t, a, v*2+1, tm+1, tr, op);
		t[v] = op(t[v*2], t[v*2+1]);
	}
}

void build(int *t, int a[], int(*op)(int, int)) {
	build_(t, a, 1, 0, n - 1, op);
}

int find_ (int *t, int v, int tl, int tr, int l, int r, int(*op)(int, int)) {
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return op(find_ (t, v*2, tl, tm, l, MIN(r,tm), op),
                  find_ (t, v*2+1, tm+1, tr, MAX(l,tm+1), r, op));
}


int find_1(int *t, int l, int r, int(*op)(int, int)) {
	return find_(t, 1, 0, n - 1, l, r, op);
}

int neutral(int(*op)(int, int)) {
    int res = op(1, 2);
    if (res == 2) return MIN_INT;
    else return 0;
}

int find_2(int *t, int left, int right, int(*op)(int, int)) {
    int res = neutral(op);
    printf("l, r\t%d %d\n", left, right);
    if (left % 2 == 1) {
        // printf("r, a[l]:\t%d %d\n", res, a[left]);
        res = op(res, a[left]);
        left++;
    }
    if (right % 2 == 0) {
        // printf("r, a[r]:\t%d %d\n", res, a[right]);
        res = op(res, a[right]);
        right--;
    }
    if (left < right) res = op(res, find_2(t, left/2, right/2, op));
    return res;
}

void update_ (int *t, int v, int tl, int tr, int pos, int new_val, int(*op)(int, int)) {
	if (tl == tr)
		t[v] = new_val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update_ (t, v*2, tl, tm, pos, new_val, op);
		else
			update_ (t, v*2+1, tm+1, tr, pos, new_val, op);
		t[v] = op(t[v*2], t[v*2+1]);
	}
}

void update (int *t, int pos, int new_val, int(*op)(int, int)) {
	update_(t, 1, 0, n - 1, pos, new_val, op);
}

int main() {
    int m;
	//scanf("%d%d", &n, &m);
	scanf("%d", &n);
	a = (int*) malloc(n * sizeof(int));

	int *t_xor = (int*) malloc(4 * n * sizeof(int));
	int *t_max = (int*) malloc(4 * n * sizeof(int));

	for (int i = 0; i < 4 * n; i++) {
		t_xor[i] = 0;
	}

	for (int i = 0; i < 4 * n; i++) {
		t_max[i] = MIN_INT;
	}

	for (int  i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	build(t_xor, a, xor_);
    build(t_max, a, max_);

    for (int i = 0; i < 4 * n; i++) {
        printf("%d\n", t_max[i]);
    }

    int l, r;
    scanf("%d%d", &l, &r);
    printf("%d", find_2(t_max, l, r, max_));

    /*
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);

        int x, y;
        int pos, val;
        switch (op) {
            case 1:
                scanf("%d%d", &x, &y);
                printf("%d\n", find_2(t_xor, x, y, xor_));
                break;
            case 2:
                scanf("%d%d", &x, &y);
                printf("%d\n", find_2(t_max, x, y, max_));
                break;
            case 3:
                scanf("%d%d", &pos, &val);
                update(t_xor, pos, val, xor_);
                update(t_max, pos, val, max_);
                break;
        }
    }
    */
}
