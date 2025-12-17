#include "../includes/treeOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Position init( int value){
    Position newElement = allocate();
    if(newElement == NULL){
        return NULL;
    }
    newElement->value = value;
    newElement->parent = NULL;
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

Position addNewEl(Position root , int value, Position parent) {
    if (root == NULL){
        Position newElement = init(value);
        newElement ->parent =  parent;
        return newElement;
    }

    if(value > root->value) root->rightChild = addNewEl(root->rightChild, value, root);
        
   else if(value < root->value) root->leftChild = addNewEl(root->leftChild, value, root);

    if(root->value == value){
        printf("Item already exists in tree!\n");
        return EXIT_SUCCESS;
    }
    
    
    return root;
}

Position findElement(Position root, int value) {
    if (root == NULL) {
        printf("Element %d doesn't exist in the tree\n", value);
        return NULL;
    }

    if (value == root->value) {
        return root;
    }
    else if (value < root->value) {
        return findElement(root->leftChild, value);
    }
    else {
        return findElement(root->rightChild, value);
    }
}
Position findMin(Position root)
{
    while (root->leftChild != NULL)
        root = root->leftChild;
    return root;
}

int deleteElement(Position root, int value)
{
    Position temp = findElement(root, value);

    if (temp == NULL) {
        printf("Element ne postoji!\n");
        return EXIT_FAILURE;
    }

    
    if (temp->leftChild != NULL && temp->rightChild != NULL) {
        Position minElement = findMin(temp->rightChild);

        temp->value = minElement->value;

        
        return deleteElement(minElement, minElement->value);
    }

    
    Position child = (temp->leftChild != NULL)
                     ? temp->leftChild
                     : temp->rightChild;

    if (temp->parent == NULL) {
        root = child;
        if (child != NULL)
            child->parent = NULL;
    }
    else if (temp->parent->leftChild == temp) {
        temp->parent->leftChild = child;
        if (child != NULL)
            child->parent = temp->parent;
    }
    else {
        temp->parent->rightChild = child;
        if (child != NULL)
            child->parent = temp->parent;
    }

    free(temp);
    return EXIT_SUCCESS;
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

int postorderPrint(Position root, int depth){
    if (root == NULL)
        return EXIT_SUCCESS;

    postorderPrint(root->leftChild, depth + 1);
    postorderPrint(root->rightChild, depth + 1);
    for (int i = 0; i < depth; i++)
        printf("|  ");
    
    printf("-> %d\n", root->value);

    return EXIT_SUCCESS;
}


int inorderPrint(Position root, int depth){
    if(root == NULL)
        return EXIT_SUCCESS;
    
    inorderPrint(root->leftChild, depth+1);
    printf("|  %*s-> %d\n", depth*2, "", root->value);
    inorderPrint(root->rightChild, depth+1);
    return EXIT_SUCCESS;

}

int printLevel(Position root, int level){
    if(root == NULL)
        return EXIT_SUCCESS;
    if(level == 1)
        printf("%d ", root->value);
    else {
        printLevel(root->leftChild, level - 1);
        printLevel(root->rightChild, level - 1);
    }
    return EXIT_SUCCESS;
}

int height(Position root){
    if(root == NULL)
        return 0;
    int lHeight = height(root->leftChild);
    int rHeight = height(root->rightChild);
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

int levelOrder(Position root){
    int h = height(root);
    for(int i = 1; i <= h; i++){
        printLevel(root, i);
        printf("\n");
    }
    return EXIT_SUCCESS;
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
int isBalanced(Position root) {
    if (!root) return 1;
    int lh = height(root->leftChild);
    int rh = height(root->rightChild);
    if (abs(lh - rh) <= 1 && isBalanced(root->leftChild) && isBalanced(root->rightChild))
        return 1;
    return 0;
}

Position findMax(Position root) {
    while (root->rightChild)
        root = root->rightChild;
    return root;
}
