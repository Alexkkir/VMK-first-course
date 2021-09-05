#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MIN_INT -2147483648

#define min(a, b) (a < b) ? a : b
#define max(a, b) (a > b) ? a : b

int n;

void build_ (int *t, int a[], int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build_ (t, a, v*2, tl, tm);
		build_ (t, a, v*2+1, tm+1, tr);
		t[v] = t[v*2] + t[v*2+1];
	}
}

void build(int *t, int a[]) {
	build_(t, a, 1, 0, n - 1);
}

int sum_ (int *t, int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return sum_ (t, v*2, tl, tm, l, min(r,tm))
		+ sum_ (t, v*2+1, tm+1, tr, max(l,tm+1), r);
}

int sum(int *t, int l, int r) {
	return sum_(t, 1, 0, n - 1, l, r);
}

void update_ (int *t, int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		t[v] = new_val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update_ (t, v*2, tl, tm, pos, new_val);
		else
			update_ (t, v*2+1, tm+1, tr, pos, new_val);
		t[v] = t[v*2] + t[v*2+1];
	}
}

void update (int *t, int pos, int new_val) {
	update_(t, 1, 0, n - 1, pos, new_val);
}

int main() {
	scanf("%d", &n);
	int a[n];

	int *t_xor = (int*) malloc(4 * n * sizeof(int));
	for (int i = 0; i < 4 * n; i++) {
		t_xor[i] = 0;
	}

	int *t_min = (int*) malloc(4 * n * sizeof(int));
	for (int i = 0; i < 4 * n; i++) {
		t_min[i] = MIN_INT;
	}

	for (int  i = 0; i < n; i++) {
		scanf("%d", a[i]);
	}

	build(t_xor, a);
	build(t_min, a);
}
