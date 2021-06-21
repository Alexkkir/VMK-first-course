#include<stdio.h>
#include <stdlib.h>
struct list {
  int key;
  struct list *next;
};

void add_end(struct list **list_p, int key) {
  struct list *new = (struct list*) malloc(sizeof(struct list));
  new->key = key;
  new->next = NULL;
  if( !(*list_p) ){
    *list_p = new;
  }
  else{
    struct list *tmp = *list_p;
    while(tmp->next) {
      tmp=tmp->next;
    }
    tmp->next = new;
  }
}

struct list * merge_lists(struct list *l1, struct list *l2) {
  struct list *ans = NULL;
  struct list *l1_tmp = l1, *l2_tmp = l2;
  while( l1_tmp || l2_tmp ){
    if(l1_tmp) {
      add_end(&ans, l1_tmp->key);
      l1_tmp = l1_tmp->next;
    }
    if(l2_tmp) {
      add_end(&ans, l2_tmp->key);
      l2_tmp = l2_tmp->next;
    }
  }
  return ans;
}

void delete_exact(struct list **list_p, struct list *elem){
  struct list *tmp = *list_p;

  if( tmp == elem ){
    (*list_p) = (*list_p)->next;
    free(elem);
    return;
  }
  else{
    while(tmp && tmp->next && tmp->next != elem) {
      tmp = tmp->next;
    }
    if( tmp && tmp->next ){
      tmp->next=elem->next;
      free(elem);
      return;
    }
  }
}

void move_elts_keys(struct list **src, struct list **dst) {
  struct list *tmp; tmp = *src;
  struct list *tmp_2;
  while(tmp) {
    if( tmp->key % 2 == 0 ){
      add_end(dst, tmp->key);
      tmp_2 = tmp->next;
      delete_exact(src, tmp);
    }
    else{
      tmp_2 = tmp->next;
    }
    tmp = tmp_2;
  }
}

void print_list(struct list *list){
  for(struct list *tmp = list; tmp; tmp = tmp->next) {
    printf("%d ", tmp->key);
  }
  printf("\n");
}

int main(){
  int l1_k[5] = {1, 2, 3, 4, 5};
  int l2_k[8] = {11, 22, 33, 44, 55, 66, 77, 88};
  struct list *list1 = NULL, *list2 = NULL;
  for(int i = 0; i < 5; i++) {
    add_end(&list1, l1_k[i]);
  }

  for(int i = 0; i < 8; i++) {
    add_end(&list2, l2_k[i]);
  }
  move_elts_keys(&list1, &list2);
  print_list(list1);
  print_list(list2);
}
