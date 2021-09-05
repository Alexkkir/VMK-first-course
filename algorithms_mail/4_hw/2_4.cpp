#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int *body;

struct bhnode {
	long long value;
	bhnode * l, * r;

	bhnode() {
        l = NULL;
        r = NULL;
	}
};

bhnode * merge (bhnode * t1, bhnode * t2) {
	if (!t1 || !t2)
		return t1 ? t1 : t2;
	if (t2->value < t1->value)
		swap (t1, t2);
	if (rand() & 1)
		swap (t1->l, t1->r);
	t1->l = merge (t1->l, t2);
	return t1;
}

void insert(bhnode *&t, long long val) {
	bhnode *p = new bhnode();
	p->value = val;
	p->l = NULL;
	p->r = NULL;

	t = merge(t, p);
}

long long pop (bhnode *&t) {
    if (!t) return -1;
    long long x = t->value;
    t = merge(t->l, t->r);
    return x;
}

void print(bhnode *t) {
	if (!t) return;
	printf("%d ", t->value);
	print(t->l);
	print(t->r);
}

int main() {
	long long n;
	scanf("%lld", &n);
	bhnode *bh = NULL;

	long long x, y;
	for (long long i = 0; i < n; i++) {
		scanf("%lld", &x);
		insert(bh, x);
	}

    long long sum = 0;
    for (long long i = n; i != 1; i--) {
        x = pop(bh);
        y = pop(bh);
        sum += x + y;
        insert(bh, x + y);
    }
    printf("%llu.%llu", sum / 100, sum % 100);
    return 0;
}
