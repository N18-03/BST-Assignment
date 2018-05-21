#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef struct Tree_node
{
    char word[20];
    struct Tree_node* left_child;
    struct Tree_node* right_child;
} Tree_node;



#endif // TREE_H_INCLUDED
