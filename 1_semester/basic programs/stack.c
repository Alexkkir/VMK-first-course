#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define datatype_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
} Node_OnceLinkedList;

void add(Node_OnceLinkedList **head_p, datatype data) {
    Node_OnceLinkedList *new = (Node_OnceLinkedList*) malloc(sizeof(Node_OnceLinkedList));
    if (new == NULL) {
        exit(1);
    }

    new->value = data;
    new->next = *head_p;
    *head_p = new;
}


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

datatype get(Node_OnceLinkedList *head){
  return head ? head->value : datatype_NULL;
}

int is_empty (Node_OnceLinkedList *head) {
  return head ? 1 : 0;
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
  Node_OnceLinkedList *stack = NULL;;

  int x;
  char c;
  int go = 1;
  while (go) {
    scanf("%c", &c);
    switch (c) {
      case 'A':
        scanf("%d", &x);
        add(&stack, x);
        break;
      case 'G':
        printf("Top: %d\n", get(stack));
        break;
      case 'P':
        print_once_linked_list(stack);
        break;
      case 'D':
        printf("Del: %d\n", pop(&stack));
        break;
      case 'F':
        go = 0;
        break;
    }
  }

}
