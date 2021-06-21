#include <stdio.h>
#include <stdlib.h>

typedef long long key_type;
typedef long long value_type;

typedef struct node // структура для представления узлов дерева
{
	key_type key;
  value_type value;
	unsigned char height;
	struct node* left;
	struct node* right;
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

node* insert(node* p, key_type k, value_type v) // вставка ключа k в дерево с корнем p
{
	if( !p ) {
    node *t = (node*) malloc (sizeof(node));
    t->key = k;
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
  else
    p->value = v;
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

node* remove_node(node* p, key_type k) // удаление ключа k из дерева p
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

void NLR_print(node* t)
{
  if(t) {
    printf("%lld %lld\n", t->key, t->value);
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
  value_type v;
  while(program_goes) {
    scanf("%c", &command);

    switch (command) {
      case 'A':
        // add
        scanf("%lld", &k);
        scanf("%lld", &v);
        tree = insert(tree, k, v);
        break;
      case 'D':
        scanf("%lld", &k);
        tree = remove_node(tree, k);
        break;
      case 'S':
        scanf("%lld", &k);
        node* t = find(tree, k);
        if (t)
          printf("%lld %lld\n", t->key, t->value);
        break;
      case 'F':
        program_goes = 0;
        break;
      default:
        break;
    }

  }
	rotated_print(tree, 0);

}
