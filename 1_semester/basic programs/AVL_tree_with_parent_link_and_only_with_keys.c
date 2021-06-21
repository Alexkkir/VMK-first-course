#include <stdio.h>
#include <stdlib.h>

typedef int key_type;

typedef struct node // структура для представления узлов дерева
{
	key_type key;
	unsigned char height;
	struct node* left;
	struct node* right;
  struct node* parent;
} node;

unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int is_first_bigger_than_second(key_type x, key_type y) {
  // для чисел
  return (x > y);
  // для строк
  // return (strcmp(x, y) > 0) ? 1 : 0;
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
  if (p->left) p->left->parent = p;
  if (p) p->parent = q;
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
  if (q) q->parent = p;
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

node* insert(node* p, key_type k) // вставка ключа k в дерево с корнем p
{
	if( !p ) {
    node *t = (node*) malloc (sizeof(node));
    t->key = k;
    t->height = 1;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;
    return t;
  }

	if(is_first_bigger_than_second(p->key, k)) {
		p->left = insert(p->left,k);
    if (p->left) p->left->parent = p;
  }
	else if (is_first_bigger_than_second(k, p->key)) {
		p->right = insert(p->right,k);
    if (p->right) p->right->parent = p;
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
  if (p->left) p->left->parent = p;
	return balance(p);
}

node* remove_node(node* p, key_type k) // удаление ключа k из дерева p
{
	if( !p ) return NULL;
	if( is_first_bigger_than_second(p->key, k) ) {
		p->left = remove_node(p->left,k);
    if (p->left) p->left->parent = p;
  }
	else if( is_first_bigger_than_second(k, p->key) ) {
		p->right = remove_node(p->right,k);
    if (p->right) p->right->parent = p;
  }
	else //  k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		free(p);
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
    if (min->right) min->right->parent = min;
		min->left = q;
    if (min->left) min->left->parent = min;
		return balance(min);
	}
	return balance(p);
}

node* find(node* p, key_type k)
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

int chech_parent_links(node* tree) {
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
  if (good == 0) printf("broken parent link in node with key = %d;\n", tree->key);
  return good & chech_parent_links(tree->left) && chech_parent_links(tree->right);
}

int chech_parent_links_for_node(node* tree) {
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

void NLR_print(node* t)
{
  if(t) {
    printf("%lld\n", t->key);
    NLR_print(t->left);
    NLR_print(t->right);
  }
}

void rotated_print(node* p, int n_level){
  if (!p) return;
  rotated_print(p->right, n_level + 1);
  for ( int i = 0; i < n_level; i++, printf("    ") );
  printf("%d\n", p->key);
  rotated_print(p->left, n_level + 1);
}

int main(void) {
  node* tree = NULL;

  char command;
  int program_goes = 1;
  key_type k;
  while(program_goes) {
    scanf("%c", &command);

    switch (command) {
      case 'A':
        // add
        scanf("%d", &k);
        tree = insert(tree, k);
        break;
      case 'D':
        scanf("%d", &k);
        tree = remove_node(tree, k);
        break;
      case 'S':
        scanf("%d", &k);
        node* t = find(tree, k);
        if (t)
          printf("there is\n");
        else printf("there is not\n");
        break;
      case 'F':
        program_goes = 0;
        break;
      case 'P':
        printf("======================\n");
        rotated_print(tree, 0);
        printf("======================\n");
        break;
      default:
        break;
    }
  }
}
