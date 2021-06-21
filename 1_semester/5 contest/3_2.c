#include <stdio.h>
#include <stdlib.h>

#define SIZE 1e9

struct stack_node{
  int key;
  struct stack_node *next, *previous;
};
typedef struct stack_node node;


void init_node(node* p, int val){
  p = (node*) malloc(sizeof(node));
  p->key = val;
  p->next = NULL;
  p->previous = NULL;
}


void add(node* p, int val){
  node* q;
  init_node(q, val);
  if (p == NULL){
    p = q;
  }
  else{
    while(p->next)
      p = p->next;
    p->next = q;
  }
  printf("***\n");

}

node* pop(node* p){
  node* ans;
  if(p == NULL){
    return NULL;
  }
  if (p->next == NULL){
    ans = p;
    free(p);
    return ans;
  }
  while(p->next->next)
    p = p->next;
  ans = p->next;
  free(p->next);
  p->next = NULL;
  return ans;
}

int main (void)
{
  node* root = NULL;
  int n;
  scanf("%d", &n);
  int x;
  for (int i = 0; i < n; i++){
    scanf("%d", &x);
    add(root, x);
  }
  node* p;
  printf("%d", root->key);
  while (1){
    p = pop(root);
    if (p)  printf("%d", p->key);
    else break;
  }
  printf("end");
}
