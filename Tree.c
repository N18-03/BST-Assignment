#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
Tree_node* root = NULL;
void inorder(Tree_node* root)
{
    if (root != NULL)
    {
        inorder(root->left_child);
        printf("%s \n", root->word);
        inorder(root->right_child);
    }
}

void construct_node(Tree_node* node, char* word)
{

    /*node->left_child = malloc(sizeof(Tree_node));
    node->right_child = malloc(sizeof(Tree_node));*/

    node->left_child = NULL;
    node->right_child = NULL;
    strcpy(node->word, word);
}

Tree_node* insert(Tree_node* start, char* inserted_word)
{

    if(start == NULL)
    {
        Tree_node* node = malloc(sizeof(Tree_node));
        construct_node(node, inserted_word);
        return node;
    }
    if(strcmp(start->word, inserted_word) < 0)
        start->right_child = insert(start->right_child, inserted_word);
    else if(strcmp(start->word, inserted_word) > 0)
        start->left_child = insert(start->left_child, inserted_word);
    else
        return start;
}

