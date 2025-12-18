#include "../includes/treeOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Position init( int value){
    Position newElement = allocate();
    if(newElement == NULL){
        return NULL;
    }
    newElement->value = value;
    newElement->leftChild = NULL;
    newElement->rightChild = NULL;
    
    return newElement;
}

Position allocate(){
    Position newElement = (Position)malloc(sizeof(Tree));
    if(newElement == NULL){
        printf("There is no enough memory!");
    }
    return newElement;
}



Position addNewEl(Position root , int value) {
    if (root == NULL){
        Position newElement = init(value);
        return newElement;
    }

    if(value >= root->value) root->leftChild = addNewEl(root->leftChild, value);
        
   else if(value < root->value) root->rightChild = addNewEl(root->rightChild, value);


    
    
    return root;
}

int replace(Position root) {
    if (root == NULL)
        return 0;


    int leftSum = replace(root->leftChild);
    int rightSum = replace(root->rightChild);

    
    int oldValue = root->value;

    
    root->value = leftSum + rightSum;

    
    return oldValue + leftSum + rightSum;
}
int preorderPrint(Position root, int depth)
{
    if (root == NULL)
        return EXIT_SUCCESS;

    for (int i = 0; i < depth; i++)
        printf("|  ");

    printf("-> %d\n", root->value);

    preorderPrint(root->leftChild, depth + 1);
    preorderPrint(root->rightChild, depth + 1);
    return EXIT_SUCCESS;
}

Position randGenTree(){
    printf("Choose how many numbers you want to generate: ");
    int num;
    int flag = 0;
    scanf("%d",&num);
    Position randRoot = init(0);

    for(int i=0;i<num;i++){
        int value = rand() % 81 + 10;
        
        if(flag==0){
             randRoot->value = value;
            flag=1;
        }
        else{
            addNewEl(randRoot, value);
        }
    }
    return randRoot;
    
    
}


int freeTree(Position root)
{
    if (root == NULL)
        return EXIT_SUCCESS;



    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root);
    return EXIT_SUCCESS;
}
