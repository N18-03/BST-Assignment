#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

Tree_node* root = NULL;


Tree_node* construct_node(char key[])
{
    Tree_node* node = (Tree_node*)
                      malloc(sizeof(Tree_node));
    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

Tree_node* insert_word(Tree_node* node, char inserted_word[])
{

    if (node == NULL)
        return(construct_node(inserted_word));

    if (strcmp(inserted_word, node->key) < 0)
        node->left  = insert_word(node->left, inserted_word);
    else if (strcmp(inserted_word, node->key) > 0)
        node->right = insert_word(node->right, inserted_word);
    else
        return node;
    node->height = 1 + get_max(get_height(node->left),
                               get_height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && strcmp(inserted_word, node->key) < 0)
        return rightRotate(node);
    if (balance < -1 && strcmp(inserted_word, node->key) > 0)
        return leftRotate(node);
    if (balance > 1 && strcmp(inserted_word, node->key) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(inserted_word, node->key) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Tree_node* loadDictionary(char *fileName, Tree_node *root)
{
    FILE *file;
    file = fopen(fileName, "r");
    if(file)
    {
        while (!feof(file))
        {
            char word[20];
            fscanf(file,"%s",word);
            root = insert_word(root, word);
        }
    }
    return root;
}

void find_p_s(Tree_node* root, char key[], Tree_node** p, Tree_node** q)
{
    // If root is null return
    if(!root)
        return ;

    // traverse the left subtree
    find_p_s(root->left, key, p, q);

    // root data is greater than a
    if(root && strcmp(key, root->key) < 0)
    {

        // q stores the node whose data is greater
        // than a and is smaller than the previously
        // stored data in *q which is sucessor
        if((!*q) || (*q) && strcmp((*q)->key, root->key) > 0)
            *q = root;
    }

    // if the root data is smaller than
    // store it in p which is predecessor
    else if(root && strcmp(key, root->key) > 0)
    {
        *p = root;
    }

    // traverse the right subtree
    find_p_s(root->right, key, p, q);
}

Tree_node* search_word(Tree_node* root, char key[])
{
    Tree_node* last_leaf = NULL;
    if (root == NULL || strcmp(key, root->key) == 0)
        return root;
    if (strcmp(key, root->key) > 0)
    {
        last_leaf = search_word(root->right, key);
        if(last_leaf == NULL)
            return root->right;
    }
    else
    {
        last_leaf = search_word(root->left, key);
        if(last_leaf == NULL)
            return root->left;
    }
    return last_leaf;
}


int get_height(Tree_node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


int get_max(int a, int b)
{
    return (a > b)? a : b;
}
Tree_node *rightRotate(Tree_node *y)
{
    Tree_node *x = y->left;
    Tree_node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = get_max(get_height(y->left), get_height(y->right))+1;
    x->height = get_max(get_height(x->left), get_height(x->right))+1;
    return x;
}

Tree_node *leftRotate(Tree_node *x)
{
    Tree_node *y = x->right;
    Tree_node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = get_max(get_height(x->left), get_height(x->right))+1;
    y->height = get_max(get_height(y->left), get_height(y->right))+1;
    return y;
}

int getBalance(Tree_node *node)
{
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}


void preOrder(Tree_node *root)
{
    if(root != NULL)
    {
        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


void check_word(char* word, Tree_node* Root)
{
    int i ;
    for(i = 0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
    }

    Tree_node *search_result = search_word(Root, word);
    Tree_node* p = NULL, *q = NULL;

    if(!strcmp(word, search_result->key))
    {
        printf("\nThe word \"%s\" exists in the English dictionary.\n",word);
    }
    else
    {
        printf("\nThe word \"%s\" is not in the dictionary. Did you mean?\n",word);
        printf("\n1.%s \n", search_result->key);
        if(search_result->key != NULL && strcmp(word, search_result->key) != 0)
        {
            find_p_s(Root, search_result->key, &p, &q);

            if(p)
                printf("2.%s \n", p->key);
            if(q)
                printf("3.%s \n", q->key);
        }

    }


}
