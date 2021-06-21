#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define datatype_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
} Node_OnceLinkedList;

Node_OnceLinkedList* get_tail(Node_OnceLinkedList *head) {
  if (!head) return NULL;

  Node_OnceLinkedList *tmp = head;
  while (tmp->next != head) {
    tmp = tmp->next;
  }
  return tmp;
}

Node_OnceLinkedList* get_before_tail(Node_OnceLinkedList *head) {
  if (!head) return NULL;

  Node_OnceLinkedList *tmp = head;
  while (tmp->next->next != head) {
    tmp = tmp->next;
  }
  return tmp;
}


void push_front(Node_OnceLinkedList **head_p, datatype data) {
    Node_OnceLinkedList *new = (Node_OnceLinkedList*) malloc(sizeof(Node_OnceLinkedList));
    if (new == NULL) {
        exit(1);
    }

    new->value = data;

    if (*head_p == NULL) {
      new->next = new;
      *head_p = new;
    }
    else {
      new->next = *head_p;
      Node_OnceLinkedList *tail = get_tail(*head_p);
      tail->next = new;
      *head_p = new;
    }
}


datatype pop_front(Node_OnceLinkedList **head_p) {
    Node_OnceLinkedList *prev, *tail;
    datatype tmp;
    if (*head_p == NULL) { // empty
        return datatype_NULL;
    }

    if ((*head_p)->next == *head_p) { // only one element
      tmp = (*head_p)->value;
      free(*head_p);
      *head_p = NULL;
      return tmp;
    }
    else {
      prev = *head_p;
      tail = get_tail(*head_p);

      *head_p = (*head_p)->next;
      // printf("%d %d %d\n", prev->value, (*head_p)->value, tail->value);
      tail->next = prev->next;
      tmp = prev->value;
      free(prev);

      return tmp;
    }

}

void push_back(Node_OnceLinkedList **head_p, datatype data) {
    push_front(head_p, data);
    *head_p = (*head_p)->next;
}

datatype pop_last(Node_OnceLinkedList **head_p) {
  *head_p = get_tail(*head_p);
  pop_front(head_p);
}

Node_OnceLinkedList* find_node_before_by_value(Node_OnceLinkedList *head, datatype value) {
  Node_OnceLinkedList *tmp = head;
  while(tmp && tmp->next && tmp->next != head && tmp->next->value != value) {
    tmp = tmp->next;
  }
  if (tmp && tmp->next && tmp->next->value == value) {
    return tmp;
  }
  else {
    return NULL;
  }
}

void delete_by_val(Node_OnceLinkedList **head_p, datatype value) {
  if (!(*head_p)) return;

  if ((*head_p)->value == value) {
    pop_front(head_p);
  }
  else {
    Node_OnceLinkedList *node_before = find_node_before_by_value(*head_p, value);
    if (!node_before) return;

    Node_OnceLinkedList *current = node_before->next;
    node_before->next = current->next;
    free(current);
  }
}

void print_once_linked_cyclic_list(Node_OnceLinkedList *list) {
    Node_OnceLinkedList *tmp = list;

    if (!tmp) return;
    do {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    } while (tmp != list);


    // while (tmp) {
    //     printf("%d ", tmp->value);
    //     tmp = tmp->next;
    // }

    printf("\n");
}

int main(void) {
  Node_OnceLinkedList *list = NULL;;

  int x;
  while (1) {
    scanf("%d", &x);
    if (x == 0) break;
    push_back(&list, x);
  }
  print_once_linked_cyclic_list(list);

  while (1) {
    scanf("%d", &x);
    if (x == 0) break;
    delete_by_val(&list, x);
    print_once_linked_cyclic_list(list);

  }
  print_once_linked_cyclic_list(list);

  printf("====\n");
  push_front(&list, 100);
  print_once_linked_cyclic_list(list);
}
