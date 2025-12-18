#include "../includes/treeOperations.h"
#include "../includes/fileOpeartions.h"
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <time.h>


int readNumbers(Position root){
    FILE *file = fopen("files/numbers.txt", "r");
    if (!file) {
           printf("Cannot open the file\n");
           return EXIT_FAILURE;
       }
    int flag = 0;
    int value;
    while(fscanf(file,"%d,", &value)==1){
        if(flag==0){
            root->value = value;
            flag = 1;
            
        }
        else{
            addNewEl(root, value);
        }
    }
    printf("Tree is generated!\n");
    fclose(file);
    return EXIT_SUCCESS;
}
int inorderPrintToFile(Position root, FILE* file){
    if(root == NULL)
        return EXIT_SUCCESS;
        
    inorderPrintToFile(root->leftChild, file);
    fprintf(file,"%d ", root->value);
    inorderPrintToFile(root->rightChild, file);
    return EXIT_SUCCESS;

}
