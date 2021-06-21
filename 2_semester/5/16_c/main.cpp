#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node // структура для представления узлов дерева
{
    char key[101];
    unsigned value;
    unsigned char height;
    struct node* left;
    struct node* right;
} node;

unsigned char height(node* p)
{
    return p ? p->height : 0;
}

int is_first_bigger_than_second(char* x, char* y) {
    return (strcmp(x, y) > 0) ? 1 : 0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, char* k, unsigned v) // вставка ключа k в дерево с корнем p
{
    if( !p ) {
        node *t = (node*) malloc (sizeof(node));
        t->key[0] = '\0';
        strcpy(t->key, k);
        t->value = v;
        t->height = 1;
        t->left = NULL;
        t->right = NULL;
        return t;
    }

    if(is_first_bigger_than_second(p->key, k))
        p->left = insert(p->left,k,v);
    else if (is_first_bigger_than_second(k, p->key))
        p->right = insert(p->right,k,v);
    else {
        p->value = v;
    }
    return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==NULL )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove_node(node* p, char* k) // удаление ключа k из дерева p
{
    if( !p ) return NULL;
    if( is_first_bigger_than_second(p->key, k) )
        p->left = remove_node(p->left,k);
    else if( is_first_bigger_than_second(k, p->key) )
        p->right = remove_node(p->right,k);
    else //  k == p->key
    {
        node* q = p->left;
        node* r = p->right;
        free(p);
        if( !r ) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

node* find(node* p, char* k)
{
    if( p ) {
        if( is_first_bigger_than_second(k, p->key) ){
            return find(p->right, k);
        }
        else if( is_first_bigger_than_second(p->key, k) ){
            return find(p->left, k);
        }
        else {
            return p;
        }
    }
    return NULL;
}

int main(void) {
    FILE *input, *output;
//    input = fopen("input.txt", "r");
//    output = fopen("output.txt", "w");

    node* tree = NULL;
    int n, m;
    char k[101];
    unsigned v;

//    fscanf(input, "%d", &n);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
//        fscanf(input, "%s%u", k, &v);
        scanf("%s%u", k, &v);
        tree = insert(tree, k, v);
    }

//    fscanf(input, "%d", &m);
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
//        fscanf(input, "%s", k);
        scanf("%s", k);

        node* elem = find(tree, k);
        if (elem) {
//            fprintf(output, "%u\n", elem->value);
            printf("%u\n", elem->value);
        }
        else {
//            fprintf(output, "-1\n");
            printf("-1\n");
        }
    }

//    fclose(input);
//    fclose(output);
}
