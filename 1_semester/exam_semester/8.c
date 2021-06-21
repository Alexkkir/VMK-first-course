#include <stdio.h>
#include <stdlib.h>

typedef int key_type;

struct tree // структура для представления узлов дерева
{
	key_type x;
	unsigned char height;
	 struct tree* left;
	 struct tree* right;
   struct tree* parent;
};

unsigned char height(struct tree* p)
{
	return p ? p->height : 0;
}

int is_first_bigger_than_second(key_type x, key_type y) {
  // для чисел
  return (x > y);
  // для строк
  // return (strcmp(x, y) > 0) ? 1 : 0;
}

int bfactor(struct tree* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(struct tree* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr)+1;
}

struct tree* rotateright(struct tree* p) // правый поворот вокруг p
{
	struct tree* q = p->left;
	p->left = q->right;
	q->right = p;
  if (p->left) p->left->parent = p;
  if (p) p->parent = q;
	fixheight(p);
	fixheight(q);
	return q;
}

struct tree* rotateleft(struct tree* q) // левый поворот вокруг q
{
	struct tree* p = q->right;
	q->right = p->left;
	p->left = q;
  if (q->right) q->right->parent = q;
  if (q) q->parent = p;
	fixheight(q);
	fixheight(p);
	return p;
}

struct tree* balance(struct tree* p) // балансировка узла p
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

struct tree* insert(struct tree* p, key_type k) // вставка ключа k в дерево с корнем p
{
	if( !p ) {
    struct tree *t = (struct tree*) malloc (sizeof(struct tree));
    t->x = k;
    t->height = 1;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;
    return t;
  }

	if(is_first_bigger_than_second(p->x, k)) {
		p->left = insert(p->left,k);
    if (p->left) p->left->parent = p;
  }
	else if (is_first_bigger_than_second(k, p->x)) {
		p->right = insert(p->right,k);
    if (p->right) p->right->parent = p;
  }
	return balance(p);
}

struct tree* findmin(struct tree* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left?findmin(p->left):p;
}

struct tree* removemin(struct tree* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==NULL )
		return p->right;
	p->left = removemin(p->left);
  if (p->left) p->left->parent = p;
	return balance(p);
}

struct tree* remove_node(struct tree* p, key_type k) // удаление ключа k из дерева p
{
	if( !p ) return NULL;
	if( is_first_bigger_than_second(p->x, k) ) {
		p->left = remove_node(p->left,k);
    if (p->left) p->left->parent = p;
  }
	else if( is_first_bigger_than_second(k, p->x) ) {
		p->right = remove_node(p->right,k);
    if (p->right) p->right->parent = p;
  }
	else //  k == p->x
	{
		struct tree* q = p->left;
		struct tree* r = p->right;
		free(p);
		if( !r ) return q;
		struct tree* min = findmin(r);
		min->right = removemin(r);
    if (min->right) min->right->parent = min;
		min->left = q;
    if (min->left) min->left->parent = min;
		return balance(min);
	}
	return balance(p);
}

struct tree* find(struct tree* p, key_type k)
{
  if( p ) {
    if( is_first_bigger_than_second(k, p->x) ){
      return find(p->right, k);
    }
    else if( is_first_bigger_than_second(p->x, k) ){
      return find(p->left, k);
    }
    else {
      return p;
    }
  }
  return NULL;
}

int chech_parent_links(struct tree* tree) {
  if (!tree) return 1;
  int good = 1;
  if (tree->left) {
    if (tree->left->parent != tree) {
      good = 0;
      printf("left\n");
    }
  }
  if (tree->right) {
    if (tree->right->parent != tree) {
      good = 0;
      printf("right\n");
    }
  }
  if (good == 0) printf("broken parent link in struct tree with x = %d;\n", tree->x);
  return good & chech_parent_links(tree->left) && chech_parent_links(tree->right);
}

int chech_parent_links_for_node(struct tree* tree) {
  if (!tree) return 1;
  int good = 1;
  if (tree->left) {
    if (tree->left->parent != tree) {
      good = 0;
    }
  }
  if (tree->right) {
    if (tree->right->parent != tree) {
      good = 0;
    }
  }
  return good;
}

void NLR_print(struct tree* t)
{
  if(t) {
    printf("%lld\n", t->x);
    NLR_print(t->left);
    NLR_print(t->right);
  }
}

void LNR_print(struct tree* t) {
  if (t) {
    LNR_print(t->left);
    printf("%d ", t->x);
    LNR_print(t->right);
  }
}

int intersection_card(struct tree *t1, struct tree *t2) {
  // будем искать узлы дерева t1 в дереве t2. рассматривать узлы t1 будем в порядке NLR;
  if(!t1 || !t2) return 0;
  int n, l, r;
  struct tree *found_n = find(t2, t1->x);

  // printf("is %d in t2? %d\n", t1->x, (found_n != NULL) ? 1 : 0);

  n = (found_n != NULL) ? 1 : 0;
  l = intersection_card(t1->left, t2);
  r = intersection_card(t1->right, t2);
  // printf("%d %d %d %d\n", t1->x, n, l, r);
  return n + l + r;
}

void rotated_print(struct tree* p, int n_level){
  if (!p) return;
  rotated_print(p->right, n_level + 1);
  for ( int i = 0; i < n_level; i++, printf("    ") );
  printf("%d\n", p->x);
  rotated_print(p->left, n_level + 1);
}

int main(void) {
  struct tree* tree1 = NULL;
  char command;
  int program_goes = 1;
  key_type k;
  while(program_goes) {
    scanf("%c", &command);

    switch (command) {
      case 'A':
        // add
        scanf("%d", &k);
        tree1 = insert(tree1, k);
        break;
      case 'D':
        scanf("%d", &k);
        tree1 = remove_node(tree1, k);
        break;
      case 'S':
        scanf("%d", &k);
        struct tree* t = find(tree1, k);
        if (t)
          printf("there is\n");
        else printf("there is not\n");
        break;
      case 'F':
        program_goes = 0;
        break;
      case 'P':
        printf("======================\n");
        rotated_print(tree1, 0);
        printf("======================\n");
        break;
      default:
        break;
    }
  }
  rotated_print(tree1, 0);

  printf("========================\n");
/*
  struct tree* tree2 = NULL;
   program_goes = 1;

  while(program_goes) {
    scanf("%c", &command);

    switch (command) {
      case 'A':
        // add
        scanf("%d", &k);
        tree2 = insert(tree2, k);
        break;
      case 'D':
        scanf("%d", &k);
        tree2 = remove_node(tree2, k);
        break;
      case 'S':
        scanf("%d", &k);
        struct tree* t = find(tree2, k);
        if (t)
          printf("there is\n");
        else printf("there is not\n");
        break;
      case 'F':
        program_goes = 0;
        break;
      case 'P':
        printf("======================\n");
        rotated_print(tree2, 0);
        printf("======================\n");
        break;
      default:
        break;
    }
  }
  rotated_print(tree2, 0);

  printf("========================\n");

  printf("%d", intersection_card(tree1, tree2));
*/
LNR_print(tree1);

}
