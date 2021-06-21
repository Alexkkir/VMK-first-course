#include <stdlib.h>
#include <stdio.h>

#define datatype int
#define int_NULL -1

typedef struct _Node {
    datatype value;
    struct _Node *next;
    struct _Node *prev;
} Node;


typedef struct _DblLinkedList {
    int size;
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


Node* getNth(DblLinkedList *list, int index) {
    Node *tmp = list->head;
    int i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

Node* getNthq(DblLinkedList *list, int index) {
    Node *tmp = NULL;
    int i;

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

void insert(DblLinkedList *list, int index, datatype value) {
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

datatype deleteNth(DblLinkedList *list, int index) {
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

void printDblLinkedList(DblLinkedList *list) {
    Node *tmp = list->head;
    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

static void QuickSort (DblLinkedList *list, int left, Node *list_left, int right, Node *list_right) {
  /* comp -- компаранд, i, j -- значения индексов */
  Node *comp;
  int tmp;
  int i, j;
  Node *list_i, *list_j; //

  i = left; j = right;
  list_i = list_left; list_j = list_right; // duplicate

  comp = getNthq(list, (left + right)/2);

  do {
    while (list_i->value < comp->value && i < right) {
      i++;
      list_i = list_i->next; //
    }
    while (comp->value < list_j->value && j > left) {
      j--;
      list_j = list_j->prev; //
    }
    if (i <= j) {
      tmp = list_i->value;
      list_i->value = list_j->value;
      list_j->value = tmp;
      i++; j--;
      list_i = list_i->next; list_j = list_j->prev; //
    }
  } while (i <= j);

  if (left < j)
    QuickSort (list, left, list_left, j, list_j);
  if (i < right)
    QuickSort (list, i, list_i, right, list_right);
}

void Qsort (DblLinkedList *list, int n) {
  QuickSort (list, 0, list->head, n - 1, list->tail);
}

int main(void) {
  DblLinkedList *list = createDblLinkedList();

  int x;
  while (1) {
    scanf("%d", &x);
    if (x == -1) break;
    pushBack(list, x);
  }

  Qsort(list, list->size);

  printDblLinkedList(list);
}
