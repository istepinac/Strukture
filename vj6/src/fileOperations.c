#include "../includes/fileOperations.h"
#include "../includes/itemsOperations.h"
#include "../includes/receiptsOperations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int createReceipts(receiptPosition head){
    FILE *file = fopen("files/receipts.txt", "r");
    
    if (file == NULL) {
        printf("Can not open receipts txt file! ");
        return EXIT_FAILURE;
    }
    
    int numOfReceipts = countReceipts();
    
    for (int i =0; i<numOfReceipts; i++) {
        char buffer[256];
        strcpy(buffer,"");
        fgets(buffer, sizeof(buffer),file);
        buffer[strcspn(buffer, "\n")] = 0;
        FILE *item = fopen(buffer,"r");
        
        if (item == NULL) {
            printf("Can not open %s txt file! ", buffer);
            return EXIT_FAILURE;
        }
        char itemBuffer[256];
        fgets(itemBuffer,sizeof(itemBuffer),item);
        itemBuffer[strcspn(itemBuffer, "\n")] = 0;

        receiptPosition newReceipt = sortAddReceipt(head,itemBuffer);
        
        while(fgets(itemBuffer,sizeof(itemBuffer),item)!=NULL){
            
            char *name = strtok(itemBuffer, ",");
            char *quantity = strtok(NULL, ",");
            char *price= strtok(NULL, ",");
            
            while(quantity[0] == ' ') quantity++;
            while(price[0] == ' ') price++;
            price[strcspn(price,"\n")]=0;
            int iQuantity = atoi(quantity);
            double dPrice= atof(price);
            
            addItemToReceipt(newReceipt, name, iQuantity, dPrice);
        }
        
        
    }
    
    return 0;
}


int countReceipts(){
    FILE *file = fopen("files/receipts.txt", "r");
    int counter =0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if(ch == '\n'){
            counter++;
        }
        
    }
    return counter;
}


int freeList(receiptPosition head){
    receiptPosition temp = head;
    while (temp!=NULL) {
        itemPosition itemTemp = temp->item;
        while(itemTemp!=NULL){
            itemPosition next = itemTemp->next;
            free(itemTemp);
            itemTemp = next;
        }
        receiptPosition next = temp->next;
        free(temp);
        temp =next;
    }
    return 0;
}

int pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    return 0;
}
