#include "rb.h"

void RedBlackTree::insertBST(Node *newNode){
    Node* parent = nullptr;
    Node* current = root;

    while(current != NIL){
        parent = current;
        if (newNode->key < current->key){
            current = current->left;
        }
        else
            current = current->right;
    }

    newNode->parent = parent;
    if(parent == nullptr) root = newNode;
    else if (newNode->key < parent-> key) parent->left = newNode;
    else parent->right = newNode;

    newNode->left = NIL;
    newNode->right = NIL;
}

void RedBlackTree::fix_insert(Node *n){
    while(n->parent != nullptr && n->parent->color == RED){
        if(n->parent == n->parent->parent->left){ // case 1: parent node is one the left side of grandparent
            Node *uncle = n->parent->parent->right;
            if(uncle->color == RED){ // case 1.1: uncle node is red: turn parent and uncle to Black and grandparent to Red; then do the fix function to the grandparent.
                n->parent->color = BLACK;
                uncle->color = BLACK;
                n->parent->parent->color = RED;
                n = n->parent->parent;
            }
            else{ // parent color = Red and uncle color = Black, indicating parent has a Black child node.
                if(n->parent->right == n){ // case 1.2: child node is on the right side of the parent. first change it to left side case.
                    n = n->parent;
                    l_rotate(n);
                }
                n->parent->parent->color = RED; // case 1.3: child node it on the left side of the parent.
                n->parent->color = BLACK;
                r_rotate(n->parent->parent);
            }
        }
        else{ // case 2: parent node is one the right side of grandparent
            Node* uncle = n->parent->parent->left;
            if(uncle->color == RED){ // case 2.1: uncle node is red: turn parent and uncle to Black and grandparent to Red; then do the fix function to the grandparent.
                n->parent->color = BLACK;
                uncle->color = BLACK;
                n->parent->parent->color = RED;
                n = n->parent->parent;
            }
            else{
                if(n->parent->left == n){ // case 2.2: child node is on the left side of the parent. first change it to right side case.
                    n = n->parent;
                    r_rotate(n);
                }
                n->parent->parent->color = RED; // case 2.3: right side case.
                n->parent->color = BLACK;
                l_rotate(n->parent->parent);
            }
        }
    }
    root->color = BLACK; // only case 1.1 or 2.1 may change the root node's color.
}

void RedBlackTree::insert(int key){
    Node *newNode = new Node(key);
    newNode->left = NIL;
    newNode->right = NIL;
    
    insertBST(newNode);
    fix_insert(newNode);
}
