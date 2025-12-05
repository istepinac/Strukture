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

int calculateItemInflation(receiptPosition head, char name[], char dateFrom[], char dateTo[]){
    receiptPosition temp = head->next;
    int flag = 0;
    double startPrice = 0.0;
    double lastPrice = 0.0;
    int itemCounter = 0;
    while(temp != NULL){
        if(strcmp(temp->date,dateFrom)>=0 && strcmp(temp->date,dateTo)<=0){
            itemPosition itemTemp = temp->item;
            while(itemTemp != NULL && strcmp(itemTemp->name,name)!=0){
                itemTemp = itemTemp->next;
            }
            if(itemTemp !=NULL){
                if (flag == 0) {
                    lastPrice = itemTemp->price;
                    startPrice = itemTemp->price;
                    itemCounter++;
                    flag =1;
                }
                else{
                    startPrice = itemTemp->price;
                    itemCounter++;
                }

                
            }
            
        }
        temp = temp->next;
    }
    
    if(itemCounter < 2){
        printf("There are not enough data points to track inflation for '%s'.\n", name);
        return  EXIT_FAILURE;
    }
    
   double percent = ((lastPrice - startPrice) / startPrice) * 100.0;
   
    
    printf("From %s to %s, item '%s' changed in price from %.2f to %.2f (%.2f%%).\n", dateFrom, dateTo,name,startPrice,lastPrice, percent);

    
    return EXIT_SUCCESS;
}



int calculateCartTotal(receiptPosition receipts) {
    double total = 0.0;

    receiptPosition cartHead = createCartList();
    itemPosition cartTemp = cartHead->item;
    while(cartTemp != NULL) {
        receiptPosition temp = receipts->next;
        double latestPrice = 0.0;
        int found = 0;

        while(temp != NULL && !found) {
            itemPosition itemTemp = temp->item;
            while(itemTemp != NULL) {
                if(strcmp(itemTemp->name, cartTemp->name) == 0) {
                    latestPrice = itemTemp->price;
                    found = 1;
                    break;
                }
                itemTemp = itemTemp->next;
            }
            temp = temp->next;
        }

        if(found) {
            total += latestPrice * cartTemp->quantity;
        } else {
            printf("Item %s is not found in receipts!\n", cartTemp->name);
        }

        cartTemp = cartTemp->next;
    }
    
    printf("Your shopping cart will cost %.2f euros.\n",total);
    

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
        printf("6 - Calculate the inflation of specific item in date range\n");
        printf("7 - Calculate your shopping cart\n");
        printf("8 - Exit program\n");

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
                printf("Enter item name:  ");
                scanf("%s",name);
                printf("Enter start date (YYYY-MM-DD): ");
                scanf("%10s", dateFrom);
                
                printf("Enter end date   (YYYY-MM-DD): ");
                scanf("%10s", dateTo);
                
                calculateItemInflation( head, name, dateFrom, dateTo);
                pauseScreen();
                break;
            
            case 7:
                calculateCartTotal(head);
                pauseScreen();
                break;

            case 8:
                printf("Exiting program...\n");
                freeList(head);
                return 0;
            default:
                break;
        }
    }
}
