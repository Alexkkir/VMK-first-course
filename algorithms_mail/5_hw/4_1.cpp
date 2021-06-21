#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

typedef long long key_type;
typedef long long value_type;

typedef struct node {
	key_type key;
	// value_type value;
	unsigned char height;
	struct node* left;
	struct node* right;
    struct node* parent;
} node;

typedef struct avl_tree {
    node *root;
    int size;

    avl_tree() {
        root = NULL;
        size = 0;
    }

    unsigned char height(node* p)
    {
        return p ? p->height : 0;
    }

    int comparator(key_type x, key_type y) {
      // ��� �����
      return (x > y);
      // ��� �����
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
        if (p->left) p->left->parent = p;
        p->parent = q;
    	fixheight(p);
    	fixheight(q);
    	return q;
    }

    node* rotateleft(node* q) // левый поворот вокруг q
    {
    	node* p = q->right;
    	q->right = p->left;
    	p->left = q;
        if (q->right) q->right->parent = q;
        q->parent = p;
    	fixheight(q);
    	fixheight(p);
    	return p;
    }

    node* balance(node* p) // балансировка узла p
    {
    	fixheight(p);
    	if( bfactor(p)==2 )
    	{
    		if( bfactor(p->right) < 0 ) {
    			p->right = rotateright(p->right);
          if (p && p->right) p->right->parent = p;
        }
    		return rotateleft(p);
    	}
    	if( bfactor(p)==-2 )
    	{
    		if( bfactor(p->left) > 0  ) {
    			p->left = rotateleft(p->left);
          if (p && p->left) p->left->parent = p;
        }
    		return rotateright(p);
    	}
    	return p; // балансировка не нужна
    }

    void insert(key_type k) {
        root = insert_(root, k);
    }

    node* insert_(node* p, key_type k) // ������� ����� k � ������ � ������ p
    {
        if( !p ) {
            node *t = (node*) malloc (sizeof(node));
            t->key = k;
            // t->value = v;
            t->height = 1;
            t->left = NULL;
            t->right = NULL;
            t->parent = NULL;
            size++;
            printf("\t\tsize++\n");
            return t;
        }

        if(comparator(p->key, k)) {
            p->left = insert_(p->left,k);
            if (p->left) p->left->parent = p;
        }
        // else if (comparator(k, p->key)) {
        else {
            p->right = insert_(p->right,k);
            if (p->right) p->right->parent = p;
        }
        // else
        //    p->value = v;
        return balance(p);
    }

    node* findmin(node* p) // ����� ���� � ����������� ������ � ������ p
    {
        return p->left ? findmin(p->left) : p;
    }

    node* findmax(node *p) {
        return p->right ? findmax(p->right) : p;
    }

    node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
    {
    	if( p->left==NULL )
    		return p->right;
    	p->left = removemin(p->left);
      if (p->left) p->left->parent = p;
    	return balance(p);
    }

    void erase(key_type k) {
        root = erase_(root, k);
    }

    node* erase_(node* p, key_type k) // �������� ����� k �� ������ p
    {
        if( !p ) return NULL;
        if( comparator(p->key, k) ) {
            p->left = erase_(p->left,k);
            if (p->left) p->left->parent = p;
        }
        else if( comparator(k, p->key) ) {
            p->right = erase_(p->right,k);
            if (p->right) p->right->parent = p;
        }
        else //  k == p->key
        {
            node* q = p->left;
    		node* r = p->right;
    		free(p);
            size--;
    		if( !r )
                return q;
    		node* min = findmin(r);
    		min->right = removemin(r);
            if (min->right)
                min->right->parent = min;
    		min->left = q;
            if (min->left)
                min->left->parent = min;
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
        //printf("==================\n");
        rotated_print_(root, 0);
        //printf("==================\n");
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

    node* find_left(node *p) {
        if (!root || !p) {
            return NULL;
        }
        if (p == findmin(root)) {
            return NULL;
        }

        // now left node 100% exist
        if (p->left) {
            node *q = p->left;
            while (q->right)
                q = q->right;
            return q;
        }
        else {
            if (!p->parent) {
                node *q = p->left;
                while (q->right)
                    q = q->right;
                return q;
            }
            else {
                if (p == p->parent->right) {
                    return p->parent;
                }
                else {
                    node *q = p;
                    while (q == q->parent->left) {
                        q = q->parent;
                    }
                    return q->parent;
                }
            }
        }
        return NULL;
    }

    node* find_right(node *p) {
        if (!root || !p) {
            return NULL;
        }
        if (p == findmax(root)) {
            return NULL;
        }

        // now left node 100% exist
        if (p->right) {
            node *q = p->right;
            while (q->left)
                q = q->left;
            return q;
        }
        else {
            if (!p->parent) {
                node *q = p->right;
                while (q->left)
                    q = q->left;
                return q;
            }
            else {
                if (p == p->parent->left) {
                    return p->parent;
                }
                else {
                    node *q = p;
                    while (q == q->parent->right) {
                        q = q->parent;
                    }
                    return q->parent;
                }
            }
        }
        return NULL;
    }

    int compare_nodes(node *n1, node *n2) {
        int bias_1 = 0, bias_2 = 0, coeff_1 = 1, coeff_2 = 1, num_steps_1 = 0, num_steps_2 = 0;

        while (n1 != root) {
            if (n1 == n1->parent->left) {
                bias_1 += coeff_1;
            }
            else {
                bias_1 -= coeff_1;
            }
            n1 = n1->parent;
            coeff_1 *= 2;
            num_steps_1++;
        }

        while (n2 != root) {
            if (n2 == n2->parent->left) {
                bias_2 += coeff_2;
            }
            else {
                bias_2 -= coeff_2;
            }
            n2 = n2->parent;
            coeff_2 *= 2;
            num_steps_2++;
        }

        if (num_steps_1 < num_steps_2) {
            for (int i = num_steps_2 - num_steps_1; i > 0; i--) {
                bias_1 *= 2;
            }
        }
        else {
            for (int i = num_steps_1 - num_steps_2; i > 0; i--) {
                bias_2 *= 2;
            }
        }

        bias_1 = -bias_1;
        bias_2 = -bias_2;

        return bias_2 - bias_1;
    }

    void median_insert(int x, node* &median) {
        if (size == 0) {
            insert(x);
            median = root;
        }

        int parity = (size % 2);
        enum {
            left,
            right
        } direction = (x < median->key) ? left : right;

        insert(x);

        printf("\t\td/p: %d %d\n", direction, parity);
        if (direction == left && parity == 1) {
            median = find_left(median);
            return;
        }
        if (direction == right && parity == 0) {
            median = find_right(median);
            return;
        }
    }

    void median_erase(int x, node* &median) {
        if (size == 1) {
            erase(x);
            median = NULL;
        }

        int parity = (size % 2);
        enum {
            left,
            right,
            unknown,
            none
        } direction = (x < median->key) ? left : ((x > median->key) ? right : unknown);

        if (direction == unknown) {
            int t = compare_nodes(find(x), median);
            if (t < 0) direction = left;
            if (t = 0) direction = none;
            if (t > 0) direction = right;
        }

        if (direction == none && parity == 0) {
            median = find_right(median);
        }
        if (direction == none && parity == 1) {
            median = find_left(median);
        }

        erase(x);

        if (direction == left && parity == 0) {
            median = find_right(median);
            return;
        }
        if (direction == right && parity == 1) {
            median = find_left(median);
            return;
        }
    }
} avl_tree;

int main(void) {
    avl_tree tree;

    int n;
    scanf("%d", &n);

    node *median = NULL;
    int op, x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &op);
        switch (op) {
            case 0:
                scanf("%d", &x);
                printf("\t\tsize: %d\n", tree.size);
                tree.median_insert(x, median);
                break;
            case 1:
                scanf("%d", &x);
                tree.median_erase(x, median);
                break;
            case 2:
                printf("\t\t%d\n", median->key);
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

/*
int comp (const int *i, const int *j)
{
return *i - *j;
}

void test_fun(int epoch, int &fails) {
    printf("\n==================\n");

    avl_tree tree;

    int n = 10;
    int *a = (int *) malloc (n * sizeof(int));
    int x, ind;

    std::srand(std::time(nullptr));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    qsort(a, n, sizeof (int), (int(*) (const void *, const void *)) comp);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    } printf("\n");

    for (int i = 0; i < n; i++) {
        tree.insert(a[i]);
    }


    tree.rotated_print();

    printf("==================\n");


    node *p, *ans;

    for (int i = 0; i < n; i++) {
        ind = rand() % (n - 1);
        x = a[ind];

        p = tree.find(x);
        ans = tree.find_right(p);

        int my_ans = ans->key;
        int corr = a[ind + 1];
        if (my_ans == corr) {
            printf(".");
        }
        else {
            printf("\nFAIL: attempt %d, x %d, my %d, corr %d\n", epoch * 100 + i, x, my_ans, corr);
            fails++;
        }
    }

    free(a);
}
*/
