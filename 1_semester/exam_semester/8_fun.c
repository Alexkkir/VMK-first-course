#include <stdlib.h>
#include <stdio.h>

typedef int key_type;

struct tree { int x; struct tree *left, *right; };

int is_first_bigger_than_second(key_type x, key_type y) {
  // для чисел
  return (x > y);
  // для строк
  // return (strcmp(x, y) > 0) ? 1 : 0;
}

struct tree* find(struct tree* p, key_type k)
{
  if( p ) {
    if( is_first_bigger_than_second(k, p->x) ){
      return find(p->right, k);
    }
    else if( is_first_bigger_than_second(p->x, k) ){
      return find(p->left, k);
    }
    else {
      return p;
    }
  }
  return NULL;
}

void LNR_print(struct tree* t) {
  if (t) {
    LNR_print(t->left);
    printf("%d ", t->x);
    LNR_print(t->right);
  }
}

int intersection_card(struct tree *t1, struct tree *t2) {
  // будем искать узлы дерева t1 в дереве t2. рассматривать узлы t1 будем в порядке NLR;
  if(!t1 || !t2) return 0;
  int n, l, r;
  struct tree *found_n = find(t2, t1->x);

  // printf("is %d in t2? %d\n", t1->x, (found_n != NULL) ? 1 : 0);

  n = (found_n != NULL) ? 1 : 0;
  l = intersection_card(t1->left, t2);
  r = intersection_card(t1->right, t2);
  // printf("%d %d %d %d\n", t1->x, n, l, r);
  return n + l + r;
}
