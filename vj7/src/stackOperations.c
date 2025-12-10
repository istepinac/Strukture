#include "../includes/stackOperations.h"
#include <stdio.h>
#include <stdlib.h>


Stack stackInit(Position dir){
    Stack newElement = stackAllocate();
    newElement->next=NULL;
    newElement->dir=dir;
    
    return newElement;
}
Stack stackAllocate(){
    Stack newElement = (Stack)malloc(sizeof(dirPosition));
    if (newElement == NULL){
        printf("Error: There is no enough memory! \n");
        return NULL;
    }
    
    return newElement;
}

int push(Stack head, Position dir){
    
    Stack newElement = stackInit(dir);
    
    newElement->next = head->next;
    head->next = newElement;
    
    return EXIT_SUCCESS;
}
int pop(Stack head){
    
    if(head->next->next == NULL){
        printf("You cannot go out of C: directory");
        return EXIT_SUCCESS;
    }
    
    Stack temp = head->next;
    head->next = temp->next;
    temp->next = NULL;
    free(temp);
    
    return EXIT_SUCCESS;
}

int freeStack(Stack stackHead){
    Stack temp = stackHead;
    while(temp!= NULL){
        Stack next = temp->next;
        temp->next = NULL;
        temp->dir = NULL;
        free(temp);
        temp=next;
    }
    return EXIT_SUCCESS;
}
