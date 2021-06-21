#include <stdlib.h>
#include <stdio.h>

#define size_t_index int
#define datatype int
#define int_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
    struct _Node *prev;
} Node;


typedef struct _DblLinkedList {
    size_t_index size;
    Node *head;
    Node *tail;
} DblLinkedList;


DblLinkedList* createDblLinkedList(void) {
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}


void pushFront(DblLinkedList *list, datatype data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}


datatype popFront(DblLinkedList *list) {
    Node *prev;
    datatype tmp;
    if (list->head == NULL) {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
    return tmp;
}


void pushBack(DblLinkedList *list, datatype data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = data;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

datatype popBack(DblLinkedList *list) {
    Node *next;
    datatype tmp;
    if (list->tail == NULL) {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    list->size--;
    return tmp;
}


Node* getNth(DblLinkedList *list, size_t_index index) {
    Node *tmp = list->head;
    size_t_index i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

Node* getNthq(DblLinkedList *list, size_t_index index) {
    Node *tmp = NULL;
    size_t_index i;

    if (index < list->size/2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}

void insert(DblLinkedList *list, size_t_index index, datatype value) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        exit(5);
    }
    ins = (Node*) malloc(sizeof(Node));
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;

    if (!elm->prev) {
        list->head = elm;
    }
    if (!elm->next) {
        list->tail = elm;
    }

    list->size++;
}

datatype deleteNth(DblLinkedList *list, size_t_index index) {
    Node *elm = NULL;
    datatype tmp = 0;
    elm = getNthq(list, index);
    if (elm == NULL) {
        exit(5);
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;

    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }
    free(elm);

    list->size--;

    return tmp;
}

datatype deleteCurrent(DblLinkedList *list, Node* elem) {
  Node *elm = NULL;
  datatype tmp = 0;
  elm = elem;
  if (elm == NULL) {
      exit(5);
  }
  if (elm->prev) {
      elm->prev->next = elm->next;
  }
  if (elm->next) {
      elm->next->prev = elm->prev;
  }
  tmp = elm->value;

  if (!elm->prev) {
      list->head = elm->next;
  }
  if (!elm->next) {
      list->tail = elm->prev;
  }
  free(elm);

  list->size--;

  return tmp;
}

void deleteAllByValue (DblLinkedList *list, datatype key) {
  Node* elm;
  elm = list->head;
  while(1) {
    while (elm && elm->value != key) {
      elm = elm->next;
    }
    if (!elm) return;
    if (!elm->next) {
      deleteCurrent(list, elm);
      return;
    }
    Node* next = elm->next;
    deleteCurrent(list, elm);
    elm = next;
  }
}

Node* findFromHeadByVal (DblLinkedList *list, datatype key) {
  Node* elm;
  elm = list->head;
  while (elm && elm->value != key) {
    elm = elm->next;
  }
  return elm;
}

Node* findFromNodeByVal (Node *node, datatype key) {
  Node* elm;
  elm = node;
  while (elm && elm->value != key) {
    elm = elm->next;
  }
  return elm;
}

Node* findFromTailByVal (DblLinkedList *list, datatype key) {
  Node* elm;
  elm = list->tail;
  while (elm && elm->value != key) {
    elm = elm->prev;
  }
  return elm;
}

void printDblLinkedList(DblLinkedList *list) {
  Node *tmp = list->head;
  while (tmp) {
    printf("%d ", tmp->value);
    tmp = tmp->next;
  }
  printf("\n");
}

void placePieceAtHead(DblLinkedList *list, int first_i, int last_i) {
  Node *first = findFromHeadByVal(list, first_i);
  //Node *last = findFromNodeByVal(first, last_i);
  Node* last = findFromTailByVal(list, last_i);

  // настраиваем стрелочки у first
  // first->prev = NULL;
  // настраиваем стрелочки у first->prev
  if (first->prev) {
    first->prev->next = last->next;
  }
  else { //иначе преобразование вида 1, last
    return;
  }
  //настраиваем стрелочки у last->next
  if (last->next) {
    last->next->prev = first->prev;
  }
  else {
    list->tail = first->prev;
  }
  last->next = list->head;
  list->head->prev = last;
  first->prev = NULL;
  list->head = first;
}

int main(void) {
  FILE *inp = fopen("input.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  DblLinkedList *list = createDblLinkedList();

  int n, k;

  fscanf (inp, "%d%d", &n, &k);

  for (int i = 1; i <= n; i++) {
    pushBack(list, i);
  }
  //printDblLinkedList(list);

  int start, end;
  for (int i = 0; i < k; i++) {
    fscanf(inp, "%d%d", &start, &end);
    placePieceAtHead(list, start, end);
  }
  //printDblLinkedList(list);

  Node *tmp = list->head;
  while (tmp) {
    fprintf(outp, "%d ", tmp->value);
    tmp = tmp->next;
  }

  fclose(inp);
  fclose(outp);
}
