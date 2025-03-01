#include "rb.h"

int main(){
    RedBlackTree rb;
    rb.insert(10);
    rb.insert(20);
    rb.insert(15);
    rb.insert(40);
    rb.deleteNode(20);
    return 0;
}