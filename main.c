#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Tree_node *root = NULL;
    root = loadDictionary("English Dictionary.txt", root);
    printf("Height of the tree is = %d", get_height(root));
    printf("\n\nenter A sentence : ");
    while(1){
        char sentence[20];
        char whitespace[2] =" ";
        scanf("%s",sentence);
        check_word(sentence, root);

        if(getchar() == '\n')
            printf("\n*******************\n");

        /*char* word = strtok(sentence, whitespace);
        while(word != NULL){
            check_word(word, root);
            printf("\n*******************\n");
            word = strtok(NULL, whitespace);
            if(word == NULL) break;
        }*/
    }

    return 0;
}
