#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
int main()
{
    Tree_node* root = malloc(sizeof(Tree_node));
    construct_node(root, "a");
    insert(root, "an");
    insert(root, "bbfb");
    insert(root, "moo");
    insert(root, "bar");


    // print inoder traversal of the BST
    inorder(root);
    return 0;
}
