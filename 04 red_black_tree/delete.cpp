#include "rb.h"

void RedBlackTree::rbTransplant(Node *u, Node *v){
    if(u->parent == nullptr){
        root = v;
    }
    else if(u->parent->left == u){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    if(v != nullptr){
        v->parent = u->parent;
    }
}

void RedBlackTree::fix_delete(Node* n){ // n is to replace the to be deleted node and it must has one or two NIL child node.
    if(n->color == RED){
        return;
    }
    else if(n->color == BLACK){ // n is originally on the left side of the parent node. It's actually add one more black node on the n's side.
        if(n->right != NIL){ // if the other child node is not NIL, then it has to be RED. so we change it to BLACK.
            n->right->color = BLACK;
            return;
        }
        else{ // the n node has only NIL child nodes.
            Node* p = n->parent;
            Node* s = p->right;
            if(s->color == RED){ // the brother node is red.
                p->color = RED;
                s->color = BLACK;
                l_rotate(p);
                
                fix_delete(n);
            }
            else if(p->color == BLACK && 
                s->color ==BLACK && 
                s->left->color == BLACK && 
                s->right->color == BLACK){
                    s->color = RED;
                    fix_delete(p);
            }
            else if(p->color == RED && 
                s->left->color == BLACK && 
                s->right->color == BLACK){
                    p->color = BLACK;
                    s->color = RED;
            }
            else if(s->color == BLACK && s->right->color == RED){
                Color color = p->color;
                p->color = s->color;
                s->color = color;
                l_rotate(p);
                s->right->color = BLACK;
            }
            else if(s->color == BLACK && s->left->color == RED){
                s->left->color = BLACK;
                s->color = RED;
                r_rotate(s);
                //go to case 4
                Color color = p->color;
                p->color = s->left->color;
                s->left->color = color;
                l_rotate(p);
                s->color = BLACK;
            }
        }
    }
}

Node* RedBlackTree::minimum(Node* node){
    while(node->left != NIL) node = node->left;
    return node;
}

void RedBlackTree::deleteNode(int val){
    Node *t = root;
    while(t != NIL){
        if(t->key == val) break;
        else if(t->key>val) t = t->left;
        else t = t->right;
    }

    if(t == NIL) return;

    Node *y;

    if(t->left == NIL){
        if(t==root || t->right == NIL){
            root = NIL;
            goto end;
        }
        y = t->right;
        fix_delete(y);
        rbTransplant(t, y);
    }
    else if(t->right == NIL){
        y = t->left;
        fix_delete(y);
        rbTransplant(t, y);
    }
    else{
        y = minimum(t->right);
        fix_delete(y);
        rbTransplant(y,y->right);
        y->right = t->right;
        y->right->parent = y;
        rbTransplant(t, y);
        y->left = t->left;
        y->left->parent = y;
    }

end:
    delete t;
}