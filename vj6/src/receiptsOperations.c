#include "../includes/receiptsOperations.h"
#include "../includes/itemsOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

receiptPosition receiptAllocate() {
    receiptPosition newElement = (receiptPosition)malloc(sizeof(Receipt));
    if (!newElement) {
        printf("Error: Not enough memory!\n");
        return NULL;
    }
    return newElement;
}

receiptPosition receiptInit() {
    receiptPosition element = receiptAllocate();
    if (!element) return NULL;

    strcpy(element->date,"0000-00-00");
    element->next = NULL;
    element->item =NULL;

    return element;
}

receiptPosition setReceiptValues(char date[]) {
    receiptPosition element = receiptAllocate();
    if (!element) return NULL;

    strcpy(element->date,date);
    element->next = NULL;
    element->item =NULL;
    return element;
}
receiptPosition sortAddReceipt(receiptPosition head,char date[]){
    receiptPosition newElement = setReceiptValues(date);
    
    if(head->next == NULL){
        newElement->next = NULL;
        head->next = newElement;
    }
    else{
        receiptPosition temp = head;
        while(temp->next != NULL && strcmp(temp->next->date,newElement->date)>0){
            temp = temp->next;
        }
        newElement->next = temp->next;
        temp->next = newElement;
    }
    
    
    return newElement;
}

int printReceipts(receiptPosition head){
    receiptPosition temp = head->next;
    
    while(temp!=NULL){
        printf("%s \n",temp->date);
        itemPosition itemTemp = temp->item;
        while(itemTemp != NULL){
            printf("%s %d %.2f \n",itemTemp->name, itemTemp->quantity, itemTemp->price);
            itemTemp = itemTemp->next;
        }
        printf("\n");
        
        temp= temp->next;
    }
    return EXIT_SUCCESS;
    
}
int printReceiptsInRange(receiptPosition head, char dateFrom[], char dateTo[]){
    receiptPosition temp = head->next;
    
    while(temp!=NULL){
        if(strcmp(temp->date,dateFrom)>=0 && strcmp(temp->date,dateTo)<=0){
            printf("%s \n",temp->date);
            itemPosition itemTemp = temp->item;
            while(itemTemp != NULL){
                printf("%s %d %.2f \n",itemTemp->name, itemTemp->quantity, itemTemp->price);
                itemTemp = itemTemp->next;
            }
            printf("\n");
            
        }
        temp= temp->next;

        }
     
    return EXIT_SUCCESS;
}

int findTheMostExpensiveReceipt(receiptPosition head){
    receiptPosition temp = head->next;
    int flag = 0;
    double maxprice = 0;
    char receiptDate[11];
    double tempPrice;

    while(temp != NULL){
        itemPosition itemTemp = temp->item;
        tempPrice=0;
        while(itemTemp != NULL){
            tempPrice += (double)itemTemp->quantity * itemTemp->price;
            itemTemp= itemTemp->next;
            
        }
        if(flag==0){
            strcpy(receiptDate,temp->date);
            maxprice = tempPrice;
            flag = 1;
        }
        else{
            if(maxprice<tempPrice){
                strcpy(receiptDate,temp->date);
                maxprice=tempPrice;
            }
        }
        
        temp = temp->next;
    }
    
    printf("The most expensive receipt is %s  - %.2f euros\n",receiptDate,maxprice);
    return EXIT_SUCCESS;
}

int findTheCheapestReceipt(receiptPosition head){
    receiptPosition temp = head->next;
    int flag = 0;
    double minprice = 0;
    char receiptDate[11];
    double tempPrice;

    while(temp != NULL){
        itemPosition itemTemp = temp->item;
        tempPrice=0;
        while(itemTemp != NULL){
            tempPrice += (double)itemTemp->quantity * itemTemp->price;
            itemTemp= itemTemp->next;
            
        }
        if(flag==0){
            strcpy(receiptDate,temp->date);
            minprice = tempPrice;
            flag = 1;
        }
        else{
            if(minprice>tempPrice){
                strcpy(receiptDate,temp->date);
                minprice=tempPrice;
            }
        }
        
        temp = temp->next;
    }
    
    printf("The cheapest receipt is %s  - %.2f euros\n",receiptDate,minprice);
    return EXIT_SUCCESS;
}
int totalMoneySpent(receiptPosition head){
    receiptPosition temp = head->next;
    double totalMoney = 0;
    int totalQuantity = 0;
    while(temp != NULL){
        itemPosition itemTemp = temp->item;
        while(itemTemp != NULL){
            totalMoney += itemTemp->price * itemTemp->quantity;
            totalQuantity += itemTemp->quantity;
            itemTemp = itemTemp->next;
        }
        temp = temp->next;
    }
    
    printf("In total you have bought %d items and spent %.2f euros\n",totalQuantity,totalMoney);
    return EXIT_SUCCESS;
}
