#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define datatype_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
} Node_OnceLinkedList;

void push_front(Node_OnceLinkedList **head_p, datatype data) {
    Node_OnceLinkedList *new = (Node_OnceLinkedList*) malloc(sizeof(Node_OnceLinkedList));
    if (new == NULL) {
        exit(1);
    }

    new->value = data;
    new->next = *head_p;
    *head_p = new;
}


datatype pop_front(Node_OnceLinkedList **head_p) {
    Node_OnceLinkedList *prev;
    datatype tmp;
    if (*head_p == NULL) {
        return datatype_NULL;
    }

    prev = *head_p;
    *head_p = (*head_p)->next;

    tmp = prev->value;
    free(prev);

    return tmp;
}

Node_OnceLinkedList* find_last(Node_OnceLinkedList *head) {
  Node_OnceLinkedList *tmp = head;
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }
  return tmp;
}

void push_back(Node_OnceLinkedList **head_p, datatype data) {
    Node_OnceLinkedList *new = (Node_OnceLinkedList*) malloc(sizeof(Node_OnceLinkedList));
    if (new == NULL) {
        exit(3);
    }
    new->value = data;
    new->next = NULL;

    if (!(*head_p)) {
      *head_p = new;
      return;
    }
    else {
      Node_OnceLinkedList *last = find_last(*head_p);
      last->next = new;
      return;
    }
}

Node_OnceLinkedList* find_before_last(Node_OnceLinkedList *head) {
  // предполагается, что head != NULL, head->next != NULL
  Node_OnceLinkedList *tmp = head;
  while (tmp && tmp->next && tmp->next->next) {
    tmp = tmp->next;
  }
  return tmp;
}

datatype pop_last(Node_OnceLinkedList **head_p) {
    Node_OnceLinkedList *next;
    datatype tmp;
    if (*head_p == NULL) {
      return datatype_NULL;
    }
    else if ((*head_p)->next == NULL) {
      tmp = (*head_p)->value;
      free(*head_p);
      *head_p = NULL;
      return tmp;
    }
    else {
      Node_OnceLinkedList *before_last = find_before_last(*head_p);
      tmp = before_last->next->value;
      free(before_last->next);
      before_last->next = NULL;
      return tmp;
    }
}

Node_OnceLinkedList* find_node_before_by_value(Node_OnceLinkedList *head, datatype value) {
  Node_OnceLinkedList *tmp = head;
  while(tmp && tmp->next && tmp->next->value != value) {
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

void print_once_linked_list(Node_OnceLinkedList *list) {
    Node_OnceLinkedList *tmp = list;
    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
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
  print_once_linked_list(list);
  while (1) {
    scanf("%d", &x);
    if (x == 0) break;
    delete_by_val(&list, x);
    print_once_linked_list(list);

  }
  // =======================
  push_back(&list,100);
  print_once_linked_list(list);

}
