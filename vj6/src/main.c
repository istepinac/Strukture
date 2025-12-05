#include <stdio.h>
#include "../includes/fileOperations.h"
#include "../includes/itemsOperations.h"
#include "../includes/receiptsOperations.h"
#define _CRT_SECURE_NO_WARNINGS

int main(){
    receiptPosition head = receiptInit();
    createReceipts(head);
    
    userOperations(head);
}

