#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int key;
  struct node *next;
} node;

node *head = NULL;

void create(node **p, int val){
  (*p) = (node*) malloc(sizeof(node));
  (*p)->next = NULL;
  (*p)->key = val;
}

void add(int val){
  if (!head){
    create(&head, val);
  }
  else {
    node *q = head;
    while(q->next)
      q = q->next;
    create(&(q->next), val);
  }
}

int pop_first(void) {
  if (!head)
    return -1;
  node* p = head;
  head = head->next;
  int a = p->key;
  free(p);
  return a;
}

void print(void) {
  node* q = head;
  while (q) {
    printf("%d ", q->key);
    q = q->next;
  }
}

int main(void){

  int to_stack = 0, x;
  while(1) {
    scanf("%d", &x);
    if (x == 0) break;
    else {
      if (!to_stack)  printf("%d ", x);
      else  add(x);
      to_stack = (to_stack + 1) % 2;
    }
  }
  print();
}
