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

bhnode * insert(bhnode *t, int val) {
	bhnode *p = (bhnode*) malloc (sizeof(bhnode));
	p->value = val;
	p->l = NULL;
	p->r = NULL;

	bhnode * ret = merge(t, p);
	return ret;
}

bhnode * delete_first(bhnode *t) {
    if (!t) return NULL;
	return merge(t->l, t->r);
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
	bhnode *bh = NULL;

	int x, y;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		bh = insert(bh, x);
	}

}
