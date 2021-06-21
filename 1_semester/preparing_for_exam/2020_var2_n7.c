#include <stdio.h>
#include <stdlib.h>


struct tree {
  int x;
  struct tree *left, *right, *parent;
};

struct tree* find_min(struct tree *t) {
  struct tree *tmp = t;
  while (tmp && tmp->left) {
    tmp = tmp->left;
  }
  return tmp;
}

void delete_min(struct tree *t) {
  struct tree *tmp = find_min(t);
  tmp->parent->left = NULL;
  free(tmp);
}

void del (struct tree *t, int x) {
  struct tree *tmp = t;
  while (tmp->x != x) {
    if (x < tmp->x) tmp = tmp->left;
    if (x > tmp->x) tmp = tmp->right;
  }
  struct tree *deleted = tmp->right;

  if (!deleted->left) {
    tmp->right = deleted->right;
    (deleted->right) ? deleted->right->parent = tmp : NULL;
    free(deleted);
  }
  else {
    deleted->x = find_min(deleted)->x;
    delete_min(deleted);
  }
}

struct tree* new(int val) {
  struct tree * new = (struct tree*) malloc(sizeof(struct tree));
  new->parent = NULL;
  new->left = NULL;
  new->right = NULL;
  new->x = val;
  return new;
}

void print_tree(struct tree* p, int n_level){
  if (!p) return;
  print_tree(p->right, n_level + 1);
  for ( int i = 0; i < n_level; i++, printf("    ") );
  printf("%d\n", p->x);
  print_tree(p->left, n_level + 1);
}


int main() {
  struct tree *n1 = new(1), *n2 = new(2), *n3 = new(3), *n4 = new(4), *n5 = new(5), *n6 = new(6), *n7 = new(7);
  n1->left = n2; n1->right = n3;
  n2->left = n4; n2->right = n5;
  n3->left = n6; n3->right = n7; n6->parent = n3;
  print_tree(n1, 0);
  del(n1, 1);
  printf("====\n");
  print_tree(n1, 0);
}
