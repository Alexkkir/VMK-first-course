#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

# if 0

struct node {
    int val;
    node *prev, *next;
};

void q_sort(node *left, node *right, int len) {
    // a[left + right / 2]
    int mid;

    node *p = left;
    for (int i = 0; i < (len - 1) / 2; i++) {
        p = p->next;
    }
    mid = p->val;

    node *i_node = left, *j_node = right;
    int i = 0, j = len - 1;

    int tmp;
    while (i <= j) {
        while (i_node->val < mid && i < len - 1) {
            i++;
            i_node = i_node->next;
        }
        while (j_node->val > mid && j > 0) {
            j--;
            j_node = j_node->prev;
        }

        if (i <= j) {
            tmp = i_node->val;
            i_node->val = j_node->val;
            j_node->val = tmp;

            i_node = i_node->next;
            j_node = j_node->prev;
            i++;
            j--;
        }
    }

    if (j > 0) {
        q_sort(left, j_node, j + 1);
    }
    if (i < len - 1) {
        q_sort(i_node, right, len - i);
    }
}

int main() {
    node *head, *tail;
    int n = 0;

    head = (node*) malloc (sizeof(node));
    head->next = NULL;
    head->prev = NULL;

    int x;
    node *p = head;
    while (scanf("%d", &x) == 1) {
        p->val = x;
        n++;

        p->next = (node*) malloc (sizeof(node));
        p->next->next = NULL;
        p->next->prev = p;

        p = p->next;
    }
    tail = p->prev;

    printf("input claimed\n");
    printf("head, tail: %d %d\n", head->val, tail->val);

    q_sort(head, tail, n);

    for (p = head; p != tail->next; p = p->next) {
        printf("%d ", p->val);
    }
    return 0;
}

# else
int main() {
    FILE *f1 = fopen("C:/Users/1/Documents/EVM/2_semester/5/input.txt", "w");

    srand(time(NULL));

    for (int i = 0; i < 400; i++) {
        fprintf(f1, "%d ", rand() % 10 - 5);
    }

}
#endif