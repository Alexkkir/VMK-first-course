#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define datatype_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
} Node_OnceLinkedList;

datatype pop(Node_OnceLinkedList **head_p) {
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

void add(Node_OnceLinkedList **head_p, datatype data) {
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

datatype get(Node_OnceLinkedList *head){
  return head ? head->value : datatype_NULL;
}


int is_empty (Node_OnceLinkedList *head) {
  return head ? 0 : 1;
}

void print_once_linked_list(Node_OnceLinkedList *list) {
    Node_OnceLinkedList *tmp = list;
    printf("->: ");
    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

int main(void) {
  Node_OnceLinkedList *queue = NULL;

  int x;
  char c;
  int go = 1;
  while (go) {
    scanf("%c", &c);
    switch (c) {
      case 'A':
        scanf("%d", &x);
        add(&queue, x);
        break;
      case 'G':
        printf("Top: %d\n", get(queue));
        break;
      case 'P':
        print_once_linked_list(queue);
        break;
      case 'D':
        printf("Del: %d\n", pop(&queue));
        break;
      case 'E':
        printf("%d\n", is_empty(queue));
        break;
      case 'F':
        go = 0;
        break;
    }
  }

}
