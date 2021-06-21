#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a, b) ((a) > (b)) ? (a) : (b)
#define min(a, b) ((a) < (b)) ? (a) : (b)

typedef int key_type;
typedef int val_t;
struct avlnode;
typedef struct avlnode *avltree;
struct avlnode {
  key_type key; //ключ
  val_t val;
  avltree left; //левое поддерево
  avltree right; //правое поддерево
  // int balance; показательбаланса
  int height; //высота поддерева
};

avltree makeempty (avltree t); //удалить дерево
avltree find (avltree t, key_type x); //поиск поключу
avltree findmin (avltree t); //минимальный ключ
avltree findmax (avltree t); //максимальный ключ
avltree insert (avltree t, key_type x, val_t y); //вставить узел
avltree delete (avltree t, key_type x); //исключить узел
void some_print(avltree t);

avltree makeempty (avltree t) {
  if (t != NULL) {
    makeempty (t->left);
    makeempty (t->right);
    free (t);
  }
  return NULL;
}

avltree find (avltree t, key_type x) {
  if (t == NULL || x == t->key)
    return t;
  if (x < t->key)
    return find (t->left, x);
  if (x > t->key)
    return find (t->right, x);
  return NULL;
}

avltree findmin (avltree t) {
  if (t == NULL)
    return NULL;
  else if (t->left == NULL)
    return t;
  else
    return findmin (t->left);
}

avltree findmax (avltree t) {
  if (t != NULL)
  while (t->right != NULL)
    t = t ->right;
  return t;
}

static inline int height (avltree p) {
  return p ? p->height : 0;
}

static inline int BalanceFactor(avltree p) {
  return p ? height(p->left) - height(p->right) : 0;
}

static avltree SingleRotateWithLeft (avltree k2) {
  avltree k1;
  /* выполнение поворота */
  k1 = k2->left;
  k2->left = k1->right; /* k1 != NULL */
  k1->right = k2;
  /* корректировка высот переставленных узлов */
  k2->height = max (height (k2->left), height (k2->right)) + 1;
  k1->height = max (height (k1->left), k2->height) + 1;
  return k1; /* новый корень */
}

static avltree SingleRotateWithRight (avltree k1) {
  avltree k2;
  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max (height (k1->left), height (k1->right)) + 1;
  k2->height = max (height (k2->right), k1->height) + 1;
  return k2; /* новый корень */
}

static avltree Balance(avltree p) {
  // fixheight(p);
	// if( bfactor(p)==2 )
	// {
	// 	if( bfactor(p->right) < 0 )
	// 		p->right = rotateright(p->right);
	// 	return rotateleft(p);
	// }
	// if( bfactor(p)==-2 )
	// {
	// 	if( bfactor(p->left) > 0  )
	// 		p->left = rotateleft(p->left);
	// 	return rotateright(p);
	// }
	// return p; // балансировка не нужна
  p->height = max(height(p->left), height(p->right)) + 1;

  if( BalanceFactor(p)==2 )
	{
		if( BalanceFactor(p->right) < 0 )
			p->right = SingleRotateWithRight(p->right);
		return SingleRotateWithLeft(p);
	}
	if( BalanceFactor(p)==-2 )
	{
		if( BalanceFactor(p->left) > 0  )
			p->left = SingleRotateWithLeft(p->left);
		return SingleRotateWithRight(p);
	}
	return p;
}

static avltree DoubleRotateWithLeft (avltree k3) {
  /* Поворот между K1 и K2 */
  k3->left = SingleRotateWithRight (k3->left);
  /* Поворот между K3 и K2 */
  return SingleRotateWithLeft (k3);
}

static avltree DoubleRotateWithRight (avltree k1) {
  /* Поворот между K3 и K2 */
  k1->right = SingleRotateWithLeft (k1->right);
  /* Поворот между K1 и K2 */
  return SingleRotateWithRight(k1);
}

avltree insert (avltree t, key_type x, val_t y) {
  if (t == NULL) {
    /* создание дерева с одним узлом */
    t = malloc (sizeof (struct avlnode));
    if (!t)
      abort();
    t->key = x;
    t->val = y;
    t->height = 1;
    t->left = NULL;
    t->right = NULL;
  }
  else if (x < t->key) {
    t->left = insert(t->left, x, y);
    if (height(t->left) - height(t->right) == 2) {
      if (x < t->left->key)
        t = SingleRotateWithLeft (t);
      else
        t = DoubleRotateWithLeft (t);
    }
  }
  else if (x > t->key) {
    t->right = insert (t->right, x, y);
    if (height(t->right) - height(t->left) == 2) {
      if (x > t->right->key)
        t = SingleRotateWithRight (t);
      else
        t = DoubleRotateWithRight (t);
    }
  }
  else if (x == t->key) {
    t->val = y;
  }
  /* иначе x уже в дереве */
  t->height = max (height (t->left), height (t->right)) + 1;
  return t;
}

avltree FindMin(avltree p) // поиск узла с минимальным ключом в дереве p
{
	return p->left ? FindMin(p->left) : p;
}

avltree RemoveMin(avltree p) // удаление узла с минимальным ключом из дерева p
{
	if(!p->left)
		return p->right;
	p->left = RemoveMin(p->left);
	return Balance(p);
}

avltree delete(avltree p, key_type k) // удаление ключа k из дерева p
{
	if( !p ) return NULL;
	if( k < p->key )
		p->left = delete(p->left,k);
	else if( k > p->key )
		p->right = delete(p->right,k);
  else //  k == p->key
	{
		avltree q = p->left;
		avltree r = p->right;
		free(p);
		if( !r ) return q;
		avltree min = FindMin(r);
		min->right = RemoveMin(r);
		min->left = q;
		return Balance(min);
	}
  return Balance(p);
}

void addElement(avltree *root_pointer, key_type x, val_t y) {
  if (*root_pointer) {
    insert(*root_pointer, x, y);
  }
  else {
    *root_pointer = insert(*root_pointer, x, y);
  }
}

void some_print(avltree t) {
  if (t) {
    printf("%lld->%lld\n", t->key, t->val);
    // printf("%lld %lld\n", t->key, t->val);
    some_print(t->left);
    some_print(t->right);
  }
}

int is_AVL(avltree t) {
  return t ? ((abs(BalanceFactor(t)) <= 1 && abs(BalanceFactor(t->left)) <= 1 && abs(BalanceFactor(t->right)) <= 1) ? 1 : 0) : 1;
}

int main (void) {

  FILE* inp = fopen("input.txt", "r");
  FILE* out = fopen("output.txt", "w");

  avltree tree = NULL;

  while (1) {
    char command;
    fscanf(inp, "%c", &command);
    // scanf("%c", &command);
    if (command == 'A') { //add
      long long x, y;
      // scanf("%lld%lld", &x, &y);
      fscanf(inp, "%lld%lld", &x, &y);
      tree = insert(tree, x, y);
    }
    if (command == 'S') { //search
      long long x;
      // scanf("%lld", &x);
      fscanf(inp, "%lld", &x);
      avltree p = find(tree, x);
      if (p)
        fprintf(out, "%lld %lld\n", p->key, p->val);
        // printf("%lld %lld\n", p->key, p->val);
    }
    if (command == 'D') {
      long long x;
      fscanf(inp, "%lld", &x);
      // scanf("%lld", &x);
      tree = delete(tree, x);
    }
    if (command == 'F') {
      break;
    }
  }

  //
  //
  // avltree tree = NULL;
  // srand(112);
  // for (int i = 0; i < 100000; i++) {
  //   int command = rand();
  //   // if (i == 98460 || i == 98461) {
  //   //   printf("=============\n");
  //   //   some_print(tree);
  //   // }
  //   if (command % 3 == 0) { // add
  //     i++;
  //     int x, y;
  //     x = rand();
  //     y = x;
  //     if (i == 98461) {
  //       printf("%d\n", x);
  //       avltree p = find(tree, x);
  //       if (p)
  //         printf("%d %d\n", p->key, p->val);
  //     }
  //     tree = insert(tree, x, y);
  //   }
  //   if (command % 3 == 1) {
  //     // search
  //     i++;
  //     int x = rand();
  //     avltree p = find(tree, x);
  //     // if (p)
  //     //   printf("%d %d\n", p->key, p->val);
  //   }
  //   if (command % 3 == 2) {
  //     // delete
  //     int x = rand();
  //     tree = delete(tree, x);
  //
  //   }
  // }
  //
  // printf("=============\n");
  // printf("%d\n", is_AVL(tree));
  // printf("=============\n");
  // some_print(tree);
}
