#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    struct tree *left;
    struct tree *right;
} tree;

void inserting(tree *root,unsigned b,unsigned c){
    tree *root1;
    root1=root;
    for (int i=0;i<32;i++){
        if ((b&c)==0){
            if (root1->left==NULL){
                root1->left=(tree *) malloc (sizeof(tree));
                root1->left->left=NULL;
                root1->left->right=NULL;
            }
            root1=root1->left;

        } else {
            if (root1->right==NULL){
                root1->right=(tree *) malloc (sizeof(tree));
                root1->right->right=NULL;
                root1->right->right=NULL;
            }
            root1=root1->right;
        }
        c>>=1;
    }
    return;
}

void deleting(tree *root, unsigned b, unsigned c){
    tree *root1 = root,*root2=root;
    int d=b&c;
    for (int i=0;i<32;i++){
        if ((b&c)==0){
            if (root1->left==NULL){
                return;
            } else {
                if (root1->right!=NULL){
                    root2=root1;
                    d=0;
                }
                root1=root1->left;
            }
        } else {
            if  (root1->right==NULL){
                return;
            } else {
                if (root1->left!=NULL){
                    root2=root1;
                    d=1;
                }
                root1=root1->right;
            }
        }
        c>>=1;
    }
    if (d==0){
        root2->left=NULL;
    } else {
        root2->right=NULL;
    }
    return;
}

void find (tree *root,unsigned b,unsigned c,unsigned d){
    tree *root1;
    root1=root;
    for (int i=0;i<32;i++){
        if ((b&c)==0){
            if (root1->right!=NULL){
                d^=c;
                root1=root1->right;
            } else {
                root1=root1->left;
            }
        } else {
            if (root1->left!=NULL){
                root1=root1->left;
            } else {
                d^=c;
                root1=root1->right;
            }
        }
        c>>=1;
    }
    printf("%u\n",d);
    return;
}

int main() {
    tree *root=NULL;
    root=(tree *) malloc (sizeof(tree));
    root->left=NULL;
    root->right=NULL;
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        unsigned a,b;
        scanf("%u%u",&a,&b);
        unsigned c=0x80000000;
        if (a==1){
            inserting(root,b,c);
        } else if (a==2){
            deleting(root, b, c);
        } else {
            find(root,b,c,0);
        }
    }

    return 0;
}
