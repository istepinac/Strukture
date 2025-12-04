#include "../includes/itemsOperations.h"
#include "../includes/receiptsOperations.h"
#include "../includes/fileOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME 30



itemPosition itemAllocate(){
    itemPosition newElement = (itemPosition)malloc(sizeof(Item));
    if (newElement == NULL){
        printf("Error: There is no enough memory! \n");
        return NULL;
    }
    return newElement;
}


itemPosition itemInit(){
    itemPosition element = itemAllocate();
    strcpy(element->name, "");
    element->price = 0.0;
    element->quantity = 0;
   
    
    return element;
}
itemPosition setItemValues(char name[],int quantity, double price){
    itemPosition element = itemAllocate();
    strcpy(element->name, name);
    element->price = price;
    element->quantity = quantity;
   
    
    return element;
}

int addItemToReceipt(receiptPosition receipt, char name[], int quantity, double price){
    itemPosition newItem = setItemValues(name, quantity, price);

    if(receipt->item ==NULL){
        newItem->next = receipt->item;
        receipt->item = newItem;
        return EXIT_SUCCESS;
        
    }
    
    if(strcmp(receipt->item->name, newItem->name) > 0){
           newItem->next = receipt->item;
           receipt->item = newItem;
           return EXIT_SUCCESS;
       }
    
        itemPosition temp = receipt->item;
        while(temp->next != NULL && strcmp(temp->next->name,newItem->name)<0){
            temp = temp->next;
        }
        
        newItem->next = temp->next;
        temp->next = newItem;
    
    
    return EXIT_SUCCESS;
}
int countItemCostInDateRange(receiptPosition head, char name[], char dateFrom[], char dateTo[]){
    receiptPosition temp = head->next;
    int quantity = 0;
    double price = 0.0;
    
    while(temp!= NULL){
        if(strcmp(temp->date,dateFrom)>=0 && strcmp(temp->date,dateTo)<=0){
            itemPosition itemTemp = temp->item;
            while(itemTemp != NULL && strcmp(itemTemp->name,name)!=0){
                itemTemp = itemTemp->next;
            }
            if(itemTemp !=NULL){
                quantity += itemTemp->quantity;
                price += itemTemp->quantity*itemTemp->price;
            }
        }
        temp = temp->next;
    }
    
    printf("From %s to %s, a total of %d %s were purchased, costing %.2f euros in total.\n",dateFrom, dateTo, quantity, name, price);
    return EXIT_SUCCESS;
}



int userOperations(receiptPosition head){
    int pick;
    
    while(1){
        printf("0 - Enter item and date range to get total cost and quantity\n");
        printf("1 - Print all receipts\n");
        printf("2 - Print receipts in date range\n");
        printf("3 - Show total money spent overall\n");
        printf("4 - Find the most expensive receipt\n");
        printf("5 - Find the cheapest receipt\n");
        printf("6 - Exit program\n");

        scanf("%d",&pick);
        switch (pick) {
            case 0:
                char dateFrom[11];
                char dateTo[11];
                char name[256];
                printf("Enter item name:  ");
                scanf("%s",name);
                printf("Enter start date (YYYY-MM-DD): ");
                scanf("%10s", dateFrom);
                
                printf("Enter end date   (YYYY-MM-DD): ");
                scanf("%10s", dateTo);
                
                

                countItemCostInDateRange(head,name,dateFrom,dateTo);
                pauseScreen();
                break;
            case 1:
                printReceipts(head);
                pauseScreen();
                break;
                
            case 2:
                
                printf("Enter start date (YYYY-MM-DD): ");
                scanf("%10s", dateFrom);
                
                printf("Enter end date   (YYYY-MM-DD): ");
                scanf("%10s", dateTo);
                printReceiptsInRange(head,dateFrom,dateTo);
                pauseScreen();
                break;
                
            case 3:
                totalMoneySpent(head);
                pauseScreen();
                break;
                
            case 4:
                findTheMostExpensiveReceipt(head);
                pauseScreen();
                break;
                
            case 5:
                findTheCheapestReceipt(head);
                pauseScreen();
                break;
                
            case 6:
                printf("Exiting program...\n");
                freeList(head);
                return 0;
            default:
                break;
        }
    }
}
