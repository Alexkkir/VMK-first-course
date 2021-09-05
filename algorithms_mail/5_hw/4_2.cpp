#include <stdio.h>
#include <stdlib.h>

typedef long long key_type;
typedef long long value_type;

typedef struct node {
	key_type key;
	// value_type value;
	unsigned char height;
	struct node* left;
	struct node* right;
} node;

typedef struct avl_tree {
    node *root;
    int len;

    avl_tree() {
        root = NULL;
        len = 0;
    }

    unsigned char height(node* p)
    {
        return p ? p->height : 0;
    }

    int comparator(key_type x, key_type y) {
      // для чисел
      return (x > y);
      // для строк
      // return (strcmp(x, y) > 0) ? 1 : 0;
    }

    int bfactor(node* p)
    {
        return height(p->right) - height(p->left);
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

    void insert(key_type k) {
        root = insert_(root, k);
    }

    node* insert_(node* p, key_type k) // вставка ключа k в дерево с корнем p
    {
        if( !p ) {
            len++;
            node *t = (node*) malloc (sizeof(node));
            t->key = k;
            // t->value = v;
            t->height = 1;
            t->left = NULL;
            t->right = NULL;
            return t;
        }

        if(comparator(p->key, k))
            p->left = insert_(p->left,k);
        else if (comparator(k, p->key))
            p->right = insert_(p->right,k);
        // else
        //    p->value = v;
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

    void erase(key_type k) {
        root = erase_(root, k);
    }

    node* erase_(node* p, key_type k) // удаление ключа k из дерева p
    {
        if( !p ) return NULL;
        if( comparator(p->key, k) )
            p->left = erase_(p->left,k);
        else if( comparator(k, p->key) )
            p->right = erase_(p->right,k);
        else //  k == p->key
        {
            len--;
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

    node* find(key_type k) {
        return find_(root, k);
    }

    node* find_(node* p, key_type k) {
        if( p ) {
            if( comparator(k, p->key) ){
                return find_(p->right, k);
            }
            else if( comparator(p->key, k) ){
                return find_(p->left, k);
            }
            else {
                return p;
            }
        }
        return NULL;
    }

    void LNR_print() {
        LNR_print_(root);
        printf("\n");
    }

    void LNR_print_(node* t)
    {
      if(t) {
        LNR_print_(t->left);
        printf("%lld ", t->key);
        LNR_print_(t->right);
      }
    }

    void rotated_print() {
        printf("==================\n");
        rotated_print_(root, 0);
        printf("==================\n");
    }

    void rotated_print_(node* p, int n_level){
      if (!p) return;
      rotated_print_(p->right, n_level + 1);
      for ( int i = 0; i < n_level; i++, printf("    ") );
      printf("%d\n", p->key);
      rotated_print_(p->left, n_level + 1);
    }

    bool is_leaf(node *p) {
        return (p->left || p->right) ? true : false;
    }

    int find_by_index(int index) {
        int curr = 0;
        long long ans = 0;
        bool in_process = true;
        find_by_index_(root, index, curr, ans, in_process);
        return ans;
    }


    void find_by_index_(node *p, int index, int &curr, long long &ans, bool &in_process) {
        if (!p || !in_process) return;

        find_by_index_(p->left, index, curr, ans, in_process);

        //printf("Cur/[] %d %d\n", curr, p->key);
        if (curr == index) {
            ans = p->key;
            in_process = false;
            curr++;
            return;
        }
        else if (curr > index) {
            in_process = false;
            return;
        }
        curr++;

        find_by_index_(p->right, index, curr, ans, in_process);
    }
} avl_tree;

int main(void) {
    avl_tree tree;

    int n;
    scanf("%d", &n);

    int op, x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &op);
        switch (op) {
            case 0:
                scanf("%d", &x);
                tree.insert(x);
                break;
            case 1:
                scanf("%d", &x);
                tree.erase(x);
                break;
            case 2:
                printf("%d\n", tree.find_by_index((1 + tree.len) / 2 - 1));
                break;
            case 3:
                tree.LNR_print();
                break;
            case 4:
                tree.rotated_print();
                break;
            default:
                break;
        }
    }
    /*
    100
    0 1
    0 2
    0 3
    0 4
    0 5
    0 6
    0 7
    1 3
    1 2
    3
    4
    2
    */
}
