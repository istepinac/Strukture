#include "../includes/treeOperations.h"
#include "../includes/stackOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Position init(char name[]){
    Position newElement = allocate();
    
    strcpy(newElement->name,name);
    newElement->next = NULL;
    newElement->child = NULL;
    
    return newElement;
}

Position allocate(){
    Position newElement = (Position)malloc(sizeof(Directory));
    if (newElement == NULL){
        printf("Error: There is no enough memory! \n");
        return NULL;
    }
    return newElement;
}


int makeDirectory(Stack stackHead, char name[]){
    if(stackHead->next == NULL){
        printf("Error: Stack is empty! \n");
        return EXIT_FAILURE;
    }
    Position current = stackHead->next->dir;
    sortAddDirectory(current,name);

    
    return EXIT_SUCCESS;
}

int sortAddDirectory(Position current, char name[]){
    Position temp = current->child;
    
    if(current->child == NULL){
        Position newDir = init(name);
        
        current->child = newDir;
        newDir->next = NULL;
        return EXIT_SUCCESS;
    }
    
    Position check = searchForName(current, name);
    if(check != NULL){
        printf("Directory named %s already exists in directory %s",name, current->name);
        return EXIT_SUCCESS;
    }
    
    Position newDir = init(name);
    if(strcasecmp(current->child->name, name) > 0){
        newDir->next = current->child;
           current->child = newDir;
           return EXIT_SUCCESS;
       }
    
        temp = current->child;
        while(temp->next != NULL && strcasecmp(temp->next->name,name)<0){
            temp = temp->next;
        }
        
    newDir->next = temp->next;
    temp->next = newDir;
    
    return EXIT_SUCCESS;
    
}

int printChildDirectories(Stack stackHead){
    if(stackHead->next == NULL){
        printf("Error: Stack is empty! \n");
        return EXIT_FAILURE;
    }
    
    Position current = stackHead->next->dir;
    
    if(current->child == NULL){
        printf("Directory %s is empty! \n",current->name);
        return EXIT_SUCCESS;
    }
    Position temp = current->child;
    printf("%s\n",current->name);
    while(temp != NULL){
        printf("|->%s\n",temp->name);
        temp = temp->next;
    }
    
    return EXIT_SUCCESS;

}

int cdDirectory(Stack stackHead, char name[] ){
    if(stackHead->next == NULL){
        printf("Error: Stack is empty! \n");
        return EXIT_FAILURE;
    }
    
    Position current = stackHead->next->dir;
    
    if(current->child == NULL){
        printf("Directory %s is empty! \n",current->name);
        return EXIT_SUCCESS;
    }
    
    Position temp = searchForName(current, name);
    
    push(stackHead, temp);
    
    
    return EXIT_SUCCESS;
}

int freeTree(Position head) {
    if (head == NULL)
        return EXIT_SUCCESS;

    freeTree(head->child);

    freeTree(head->next);
    
    free(head);
    return EXIT_SUCCESS;
}

int deleteDir(Position current, char name[]) {
    if (current->child == NULL) {
        printf("Directory %s is empty!\n", current->name);
        return EXIT_SUCCESS;
    }

    Position temp = current->child;
    Position prev = NULL;

    
    while (temp != NULL && strcasecmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("There is no directory named %s in directory %s\n", name, current->name);
        return EXIT_SUCCESS;
    }


    if (prev == NULL) {
        current->child = temp->next;
    } else {
        prev->next = temp->next;
    }

    freeTree(temp);

    printf("Directory %s deleted successfully.\n", name);
    return EXIT_SUCCESS;
}

int renameDir(Position current, char oldName[], char newName[]){
    
    Position temp = searchForName(current, oldName);
    
    strcpy(temp->name, newName);
    return EXIT_SUCCESS;
}

Position searchForName(Position head, char name[]){
    if (head->child == NULL) {
        printf("Directory %s is empty!\n", head->name);
        return EXIT_SUCCESS;
    }

    Position temp = head->child;

    
    while (temp != NULL && strcasecmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("There is no directory named %s in directory %s\n", name, head->name);
        return NULL;
    }
    
    return temp;
}
