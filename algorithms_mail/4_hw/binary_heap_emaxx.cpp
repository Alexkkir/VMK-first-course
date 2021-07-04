#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct bhnode {
	int value;
	bhnode * l, * r;
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

void insert(bhnode **t_p, int val) {
	bhnode *p = (bhnode*) malloc (sizeof(bhnode));
	bhnode *t = *t_p;
	p->value = val;
	p->l = NULL;
	p->r = NULL;
	*t_p = merge(t, p);
}

int pop(bhnode **t_p) {
	bhnode *t = *t_p;
	printf("here\n");
	if (t == NULL) {
		printf("return -1");
		return -1;
	}
	printf("return SMTH\n");
	int ret = t->value;
	*t_p = merge(t->l, t->r);
	free(t);
	return ret;
}

void print(bhnode *t) {
	if (!t) return;
	printf("%d ", t->value);
	print(t->l);
	print(t->r);
}

int main() {
	// FILE *f = fopen("inp.txt", "r");
	int n;
	scanf("%d", &n);
	bhnode *bh;

	int x, y;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		insert(&bh, x);
	}

	int a;
	a = pop(&bh);
	print(bh);

}
