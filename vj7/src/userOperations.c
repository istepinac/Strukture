#include "../includes/treeOperations.h"
#include "../includes/userOperations.h"
#include "../includes/stackOperations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int userOperations(Position head, Stack stackHead){
    int pick;
    while(1){
        printf("\nChoose a command:\n");
          printf("1 - md\n");
          printf("2 - cd dir\n");
          printf("3 - cd..\n");
          printf("4 - dir\n");
          printf("5 - rd /s dir\n");
          printf("6 - ren old_name new_name\n");
          printf("7 - exit\n");
          printf("Enter your choice: ");

        scanf("%d",&pick);
        switch (pick) {
            case 1:
                char name[50];
                printf("Enter the name of the directory: ");
                scanf("%s",name);
                makeDirectory(stackHead,name);
                break;
            case 2:
                printf("Enter the name of the directory: ");
                scanf("%s",name);

                cdDirectory(stackHead,name);
                break;
                
            case 3:
                pop(stackHead);
                break;
            case 4:
                printChildDirectories(stackHead);
                break;
            case 5:
                if(stackHead->next->dir->child == NULL){
                    printf("C: folder is empty!\n");
                    break;
                }
                Position current = stackHead->next->dir;
                printf("Enter the name of the directory you want to delete: ");
                scanf("%s",name);
                deleteDir(current,name);
                break;
            case 6:
                if(stackHead->next->dir->child == NULL){
                    printf("C: folder is empty!\n");
                    break;
                }
                char oldName[50];
                char newName[50];
                printf("Enter old name and the name you want to swap it:  ");
                scanf("%s %s",oldName,newName);
                current = stackHead->next->dir;
                renameDir(current, oldName, newName);
                break;
                
            case 7:
                printf("Exiting program...\n");
                freeTree(head);
                freeStack(stackHead);
                return EXIT_SUCCESS;
            default:
                break;
        }
    }
    
}
