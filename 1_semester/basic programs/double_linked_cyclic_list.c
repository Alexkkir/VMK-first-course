#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define datatype_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next, *prev;
} Node_DoubleLinkedList;

Node_DoubleLinkedList* get_tail(Node_DoubleLinkedList *head) {
  if (!head) return NULL;

  return head->prev;
}

Node_DoubleLinkedList* get_before_tail(Node_DoubleLinkedList *head) {
  if (!head) return NULL;

  return head->prev->prev;
}


void push_front(Node_DoubleLinkedList **head_p, datatype data) {
    Node_DoubleLinkedList *new = (Node_DoubleLinkedList*) malloc(sizeof(Node_DoubleLinkedList));
    if (new == NULL) {
        exit(1);
    }

    new->value = data;

    if (*head_p == NULL) {
      new->next = new;
      new->prev = new;
      *head_p = new;
    }
    else {
      Node_DoubleLinkedList *tail = get_tail(*head_p);
      new->next = *head_p;
      new->prev = tail;
      tail->next = new;
      (*head_p)->prev = new;

      *head_p = new;
    }
}


datatype pop_front(Node_DoubleLinkedList **head_p) {
    Node_DoubleLinkedList *prev, *tail;
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
      (*head_p)->prev = tail;
      tmp = prev->value;
      free(prev);

      return tmp;
    }

}

void push_back(Node_DoubleLinkedList **head_p, datatype data) {
    push_front(head_p, data);
    *head_p = (*head_p)->next;
}

datatype pop_last(Node_DoubleLinkedList **head_p) {
  *head_p = get_tail(*head_p);
  pop_front(head_p);
}

Node_DoubleLinkedList* find_node_before_by_value(Node_DoubleLinkedList *head, datatype value) {
  // NULL, if length = 0 or node with x key is absent
  Node_DoubleLinkedList *tmp = head;
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

void delete_by_val(Node_DoubleLinkedList **head_p, datatype value) {
  if (!(*head_p)) return;

  if ((*head_p)->value == value) {
    pop_front(head_p);
  }
  else {
    Node_DoubleLinkedList *node_before = find_node_before_by_value(*head_p, value);
    if (!node_before) return;

    Node_DoubleLinkedList *current = node_before->next;
    node_before->next = current->next;
    current->next->prev = node_before;
    free(current);
  }
}

void print_once_linked_cyclic_list(Node_DoubleLinkedList *head) {
    Node_DoubleLinkedList *tmp = head;

    if (!tmp) {
      printf("->:\n<-:\n");
      return;
    }
    printf("->: ");
    do {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");

    Node_DoubleLinkedList *tail = get_tail(head);
    tmp = tail;
    if (!tmp) return;
    printf("<-: ");
    do {
        printf("%d ", tmp->value);
        tmp = tmp->prev;
    } while (tmp != tail);

    printf("\n");
}

int main(void) {
  Node_DoubleLinkedList *list = NULL;;

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

  printf("====\n");
  push_front(&list, 100);
  print_once_linked_cyclic_list(list);
}
