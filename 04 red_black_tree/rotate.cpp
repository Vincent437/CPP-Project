#include "rb.h"

void RedBlackTree::l_rotate(Node *x){
    Node *y = x->right;

    x->right = y->left;

    if(y->left != NIL){
        y->left->parent = x;
    }

    y->parent = x->parent;
    if(x->parent==nullptr){
        root = y;
    }
    else if(x->parent->left == x){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void RedBlackTree::r_rotate(Node *x){
    Node *y = x->left;
    
    x->left = y->right;
    if(y->right != NIL){
        y->right =x;
    }

    y->parent = x->parent;
    if(x->parent == nullptr){
        root = y;
    }
    else if(x->parent->left == x){
        x->parent->left =y;
    }
    else{
        x->parent->right =y;
    }

    x->parent = y;
    y->right =x;
}