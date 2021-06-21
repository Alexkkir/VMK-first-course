#include <stdlib.h>
#include <stdio.h>

struct avltree{
  int key;
  struct avltree *left;
  struct avltree *right;
};


void set_keys(struct avltree *tree, int *n){
  if(!tree) return;
  set_keys(tree->left, n);
  tree->key = *n; (*n)++;
  set_keys(tree->right, n);
}

struct avltree *build_form(int h){
  if (h == 0){
    return NULL;
  }
  if (h == 1){
    struct avltree *tmp = (struct avltree*) malloc(sizeof(struct avltree));
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
  }
  if (h > 1){
    struct avltree *tmp = (struct avltree*) malloc(sizeof(struct avltree));
    tmp->left = build_form(h-2);
    tmp->right = build_form(h-1);
    return tmp;
  }
}

struct avltree *build(int h){
  struct avltree *tree = build_form(h);
  int n = 1;
  set_keys(tree, &n);
  return tree;
}

void print(struct avltree *tree){
  if(!tree) return;
  print(tree->left);
  printf("%d ", tree->key);
  print(tree->right);
}

int main(void) {
  struct avltree *tree = build(4);
  print(tree);
  return 0;
}
