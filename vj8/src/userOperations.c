#include "../includes/treeOperations.h"
#include "../includes/userOperations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int userOperations(){
    printf("Insert the root of the table: ");
    int value;
    scanf("%d",&value);
    Position root = init(value);
    int pick;
    while(1){
        printf("\nChoose a command:\n");
        printf("1 - add new element to tree\n");
        printf("2 - inorder print\n");
        printf("3 - preorder print\n");
        printf("4 - postorder print\n");
        printf("5 - levelorder print\n");
        printf("6 - delete element\n");
        printf("7 - find element\n");
        printf("8 - calculate depth of the tree\n");
        printf("9 - check if tree is balanced\n");
        printf("10 - find the minimum value in the tree\n");
        printf("11 - find the maximum value in the tree\n");
        printf("12- exit\n");
        printf("Enter your choice: ");

        scanf("%d",&pick);
        switch (pick) {
            case 1:
                printf("Enter the value of the new element: ");
                scanf("%d",&value);
                addNewEl(root, value,NULL);
                pauseScreen();
                break;
            case 2:
                inorderPrint(root, 0);
                pauseScreen();
                break;
                
            case 3:
                preorderPrint(root,0);
                pauseScreen();
                break;
            case 4:
                postorderPrint(root,0);
                pauseScreen();
                break;
            case 5:
                levelOrder(root);
                pauseScreen();
                break;
            case 6:
                    printf("Enter the value of the element to delete: ");
                    scanf("%d",&value);
                    deleteElement(root,value);
                    pauseScreen();
                    break;
                
                
            case 7:
                printf("Enter the value of the element to find: ");
                if( findElement(root, value) != NULL){
                    printf("Element has been found!\n");
                }
                pauseScreen();
                break;
            case 8:
                printf("The depth of the tree is: %d",height(root));
                pauseScreen();
                break;
            case 9:
                if(isBalanced(root))
                    printf("The tree is balanced!\n");
                else
                    printf("The tree is not balanced!\n");
                pauseScreen();
                break;
            case 10:
                printf("The minimum value in the tree is: %d\n",findMin(root)->value);
                pauseScreen();
                break;
            case 11:
                printf("The maximum value in the tree is: %d\n",findMax(root)->value);
                pauseScreen();
                break;
              
            case 12:
                printf("Exiting program...\n");
                freeTree(root);
                return EXIT_SUCCESS;
            default:
                break;
        }
    }
    
}

int pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    return 0;
}
