enum Color { RED, BLACK };

struct Node{
    int key;
    Color color;
    Node *left, *right, *parent;

    Node( int key ) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree{
    private:
    Node *root;
    Node *NIL;

    public:
    Node* get_root(){return root;}

    RedBlackTree(){
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

    void l_rotate(Node *x);
    void r_rotate(Node *x);

    void insertBST(Node *newNode);    
    void fix_insert(Node *n);
    void insert(int key);

    Node* minimum(Node *node);
    void rbTransplant(Node *u, Node *v);
    void fix_delete(Node* node);
    void deleteNode(int val);
};
