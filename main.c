// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// An AVL tree node
struct Node
{
    char key[20];
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(char key[])
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct Node* node, char key[])
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (strcmp(key, node->key) < 0)
        node->left  = insert(node->left, key);
    else if (strcmp(key, node->key) > 0)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(key, node->key) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(key, node->key) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(key, node->key) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(key, node->key) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//Load Dictionary
struct Node* loadDictionary(char *fileName, struct Node *root)
{
    FILE *file;
    int i = 0;
    file = fopen(fileName, "r");
    if(file)
    {
        while (!feof(file))
        {
            char word[20];
            fscanf(file,"%s",word);
            root = insert(root, word);
        }
    }
    return root;
}

// C function to search a given key in a given BST
struct Node* search(struct Node* root, char key[])
{
    struct Node* last_leaf = NULL;
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(key, root->key) == 0)
       return root;

    // Key is greater than root's key
    if (strcmp(key, root->key) > 0) {
       last_leaf = search(root->right, key);
       if(last_leaf == NULL)
            return root->right;
    }
    // Key is smaller than root's key
    else {
        last_leaf = search(root->left, key);
        if(last_leaf == NULL)
            return root->left;
    }
    return last_leaf;
}

void find_p_s(struct Node* root, char key[], struct Node** p, struct Node** q)
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

/* Drier program to test above function*/
int main()
{
    struct Node *root = NULL;
    root = loadDictionary("English Dictionary.txt", root);
    printf("height = %d\n\n", height(root));

    while(1){
        char key[20];
        int i;
        printf("enter search word : ");
        scanf("%s",key);

        //convert each character to lowercase.
        for(i = 0; key[i]; i++){
            key[i] = tolower(key[i]);
        }

        struct Node *search_result = search(root, key);
        struct Node* p = NULL, *q = NULL;

        printf("%s \n", search_result->key);
        if(search_result->key != NULL && strcmp(key, search_result->key) != 0){
            find_p_s(root, search_result->key, &p, &q);

            if(p) printf("%s \n", p->key);
            if(q) printf("%s \n", q->key);
        }
        printf("\n");
    }
    return 0;
}
