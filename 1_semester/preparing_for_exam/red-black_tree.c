#include <stdio.h>
#include <stdlib.h>

struct node{
  int key;
  enum {
    RED,
    BLACK
  } color;
  struct node *parent, *left, *right;
};

int is_leaf(struct node *n);
struct node* grandparent(struct node *n);
struct node* uncle(struct node *n);
struct node* sibling(struct node *n);
void rotate_left(struct node *n);
void rotate_right(struct node *n);

void insert_case1(struct node *n);
void insert_case2(struct node *n);
void insert_case3(struct node *n);
void insert_case4(struct node *n);
void insert_case5(struct node *n);

void replace_node(struct node* n, struct node* child);
void delete_one_child(struct node *n);

void delete_case1(struct node *n);
void delete_case2(struct node *n);
void delete_case3(struct node *n);
void delete_case4(struct node *n);
void delete_case5(struct node *n);
void delete_case6(struct node *n);

int is_leaf(struct node *n){
  if (n && n->left && n->right && !n->left->left && !n->left->right && !n->right->left && !n->right->left)
    return 1;
  else
    return 0;
}

struct node* grandparent(struct node *n){
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

struct node* uncle(struct node *n){
	struct node *g = grandparent(n);
	if (g == NULL)
		return NULL; // No grandparent means no uncle
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

struct node *sibling(struct node *n){
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void rotate_left(struct node *n){
    struct node *pivot = n->right;

    pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (n->parent != NULL) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->right = pivot->left;
    if (pivot->left != NULL)
        pivot->left->parent = n;

    n->parent = pivot;
    pivot->left = n;
}

void rotate_right(struct node *n){
    struct node *pivot = n->left;

    pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (n->parent != NULL) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->left = pivot->right;
    if (pivot->right != NULL)
        pivot->right->parent = n;

    n->parent = pivot;
    pivot->right = n;
}

void insert(struct node **tree_p, int k){
  struct node* new = (struct node*) malloc(sizeof(struct node));
  new->key = k;
  new->color = RED;
  new->left = NULL;
  new->right = NULL;
  new->parent = NULL;

  struct node* new_l = (struct node*) malloc(sizeof(struct node));
  struct node* new_r = (struct node*) malloc(sizeof(struct node));
  new_l->left = NULL;
  new_l->right = NULL;
  new_l->parent = new;

  new_r->left = NULL;
  new_r->right = NULL;
  new_r->parent = new;

  if ( !(*tree_p) ){
    *tree_p = new;
  }
  else {
    struct node* tmp;
    tmp = *tree_p;

    while( is_leaf(tmp) ){ // ищем ущел посло которого будем вставлять
      if (k < tmp->key){
        if ( is_leaf(tmp->left) ){
          tmp = tmp->left;
        }
        else {
          break;
        }
      }
      else if (k > tmp->key){
        if ( is_leaf(tmp->right) ){
          tmp = tmp->right;
        }
        else {
          break;
        }
      }
    }

    if( k < tmp->key ){
      tmp->left = new;
      new->parent = tmp;
    }
    else if( k > tmp->key ){
      tmp->right = new;
      new->parent = tmp;
    }
    else if (k == tmp->key) {
      free(new);
      return;
    }
  }

  insert_case1(new);
}

void insert_case1(struct node *n){
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}

void insert_case2(struct node *n){
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(struct node *n){
	struct node *u = uncle(n), *g;

	if ((u != NULL) && (u->color == RED)) {
	// && (n->parent->color == RED) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(g);
	}
  else {
		insert_case4(n);
	}
}

void insert_case4(struct node *n){
	struct node *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotate_left(n->parent);
		n = n->left;
	}
  else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void insert_case5(struct node *n)
{
	struct node *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate_right(g);
	}
  else { /* (n == n->parent->right) && (n->parent == g->right) */
		rotate_left(g);
	}
}

void replace_node(struct node* n, struct node* child) {
    child->parent = n->parent;
    if (n == n->parent->left) {
        n->parent->left = child;
    }
    else {
        n->parent->right = child;
    }
}

void delete_one_child(struct node *n){
	/*
	 * Условие: n имеет не более одного ненулевого потомка.
	 */
	struct node *child = is_leaf(n->right) ? n->left : n->right;

	replace_node(n, child);
	if (n->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_case1(child);
	}
	free(n);
}

void delete_case1(struct node *n){
	if (n->parent != NULL)
		delete_case2(n);
}

void delete_case2(struct node *n){
	struct node *s = sibling(n);

	if (s->color == RED) {
		n->parent->color = RED;
		s->color = BLACK;
		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	}
	delete_case3(n);
}

void delete_case3(struct node *n){
	struct node *s = sibling(n);

	if ((n->parent->color == BLACK) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {
		s->color = RED;
		delete_case1(n->parent);
	} else
		delete_case4(n);
}

void delete_case4(struct node *n){
	struct node *s = sibling(n);

	if ((n->parent->color == RED) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {
		s->color = RED;
		n->parent->color = BLACK;
	} else
		delete_case5(n);
}

void delete_case5(struct node *n){
	struct node *s = sibling(n);

	if  (s->color == BLACK) { /* this if statement is trivial,
due to case 2 (even though case 2 changed the sibling to a sibling's child,
the sibling's child can't be red, since no red parent can have a red child). */
/* the following statements just force the red to be on the left of the left of the parent,
   or right of the right, so case six will rotate correctly. */
		if ((n == n->parent->left) &&
		    (s->right->color == BLACK) &&
		    (s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(s);
		} else if ((n == n->parent->right) &&
		           (s->left->color == BLACK) &&
		           (s->right->color == RED)) {/* this last test is trivial too due to cases 2-4. */
			s->color = RED;
			s->right->color = BLACK;
			rotate_left(s);
		}
	}
	delete_case6(n);
}

void delete_case6(struct node *n){
	struct node *s = sibling(n);

	s->color = n->parent->color;
    n->parent->color = BLACK;

	if (n == n->parent->left) {
        s->right->color = BLACK;
		rotate_left(n->parent);
	} else {
		s->left->color = BLACK;
		rotate_right(n->parent);
	}
}

void print_tree(struct node* p, int n_level){
  if (!p) return;
  print_tree(p->right, n_level + 1);
  for ( int i = 0; i < n_level; i++, printf("\t") );
  printf("%d\n", p->key);
  //p->color == RED ? printf("RED") : printf("BLACK");
  print_tree(p->left, n_level + 1);
}

int main(void) {
  int keys[10] = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
  struct node *tree = NULL;
  for (int i = 0; i < 10; i++){
    insert(&tree, keys[i]);
  }

  print_tree(tree, 0);
  printf("end");
}
