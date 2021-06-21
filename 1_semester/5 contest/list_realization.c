#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int key;
  struct node *next;
} node;

node *head = NULL, *ret;

void list_init(void);
void delete_list(void);
void create(node **p, int val);
void initialize_with_node(node **p, node* q);
void add_to_end(int val);
void add_to_head(int val);
void add_to_end_if_doesnt_exist(int val);
void add_to_head_if_doesnt_exist(int val);
node* find (int val);
node* find_before(int val);
node* pop_last(void);
node* pop_first(void);
node* delete_by_val(int val);
void print(void);
void print_node(node* p);

int main(void){
  list_init();

  int x, counter = 0;
  while(1) {
    scanf("%d", &x);
    if (x == 0)
      break;
    add_to_head(x);
  }

  if (head) {
    node* q = head;
    while (q) {
      if (q->key < head->key) {
        counter++;
      }
      q = q->next;
    }
  }
  printf("%d", counter);
  delete_list();
}


// ====================================================

void list_init(void) {
  create(&ret, 0);
}

void delete_list(void) {
  free(ret);
  node* p = head;
  if (!p)
    return;
  else {
    node* q = head->next;
    while (q) {
      free(p);
      p = q;
      q = q->next;
    }
    free(p);
  }
}

void create(node **p, int val){
  (*p) = (node*) malloc(sizeof(node));
  (*p)->next = NULL;
  (*p)->key = val;
}

void initialize_with_node(node **p, node* q){
  if (q) {
    (*p)->key = q->key;
    (*p)->next = q->next;
  }
  else {
    (*p)->key = 0;
    (*p)->next = NULL;
  }
}

void add_to_head(int val){
  if (!head) {
    create(&head, val);
  }
  else {
    node* q;
    create(&q, val);
    q->next = head;
    head = q;
  }
}

void add_to_end(int val){
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

node* pop_last(void) {
  if (!head)
    return NULL;

  if (!(head->next)) {
    initialize_with_node(&ret, head);
    free(head);
    head = NULL;
    return ret;
    /*
    a = head->key;
    free(head);
    head = NULL;
    return a;*/
  }

  else {
    node* q = head;
    while (q->next->next)
      q = q->next;
    initialize_with_node(&ret, q->next);
    free(q->next);
    q->next = NULL;
    return ret;
      /*
    a = q->next->key;
    free(q->next);
    q->next = NULL;
    return a; */
  }
}

node* pop_first(void) {
  if (!head)
    return NULL;
  node* p = head;
  head = head->next;
  initialize_with_node(&ret, p);
  free(p);
  return ret;
}

node* find (int val) {
  node* p = head;
  while (p && p->key != val)
    p = p->next;
  return p;
}

node* find_before(int val) {
  node* p = head;
  if (!head) {
    return NULL;
  }
  else {
    if (head->key == val) {
        initialize_with_node(&ret, NULL);
        ret->next = head;
        return ret;
    }
    else {
      while (p->next && p->next->key != val) {
        p = p->next;
      }
      if (p->next)
        return p;
      else
        return NULL;
    }
  }
}

void add_to_end_if_doesnt_exist(int val) {
  node* p = find_before(val);
  if (!p) {
    add_to_end(val);   // тут нужно выбрать подходящую функцию - add_to_end или add_to_head
  }
}

void add_to_head_if_doesnt_exist(int val) {
  node* p = find_before(val);
  if (!p) {
    add_to_head(val);   // тут нужно выбрать подходящую функцию - add_to_end или add_to_head
  }
}

node* delete_by_val(int val) {
  node* p = find_before(val);
  if (p) {
    if (p->next && p->next == head) {

      node* q = head;
      head = head->next;
      initialize_with_node(&ret, q);

      free(q);
      return ret;
    }
    else {
      node* q;
      q = p->next;
      initialize_with_node(&ret, q);
      p->next = q->next;
      free(q);
      return ret;
    }
  }
  else {
    return NULL;
  }
}

void print(void) {
  node* q = head;
  while (q) {
    printf("%d ", q->key);
    q = q->next;
  }
  printf("\n");
}

void print_node(node* p) {
  if (p != NULL) {
    printf("%d ", p->key);
  }
}
