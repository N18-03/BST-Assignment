#ifndef TREE_H_INCLUDED
typedef struct Tree_node
{
    char key[20];
    struct Tree_node *left;
    struct Tree_node *right;
    int height;
}Tree_node;

Tree_node* construct_node(char key[]);

Tree_node* insert_word(Tree_node* node, char key[]);

Tree_node* search_word(Tree_node* root, char key[]);

Tree_node* loadDictionary(char *fileName, Tree_node *root);

void find_p_s(Tree_node* root, char key[], Tree_node** p, Tree_node** q);

Tree_node *leftRotate(Tree_node *x);

Tree_node *rightRotate(Tree_node *y);

int get_max(int a, int b);

int get_height(Tree_node *N);

int getBalance(Tree_node *node);

void preOrder(Tree_node *root);

void check_word(char* word, Tree_node* Root);


#endif // TREE_H_INCLUDED
