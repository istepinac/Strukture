#ifndef RECEIPTS_OPERATIONS_H
#define RECEIPTS_OPERATIONS_H

typedef struct Receipt* receiptPosition;
typedef struct Item* itemPosition;

typedef struct Receipt {
    char date[11];
    receiptPosition next;
    itemPosition item;
} Receipt;

receiptPosition receiptAllocate(); //funkcija koja alocira memoriju za racune
receiptPosition receiptInit(); //funkcija koja postavlja vrijednoti racuna na 0/NULL
receiptPosition sortAddReceipt(receiptPosition head,char date[]); //funkcija koja sortirano dodaje racune u listu
receiptPosition setReceiptValues(char date[]);//funkcija koja postavlja vrijednosti racuna na zadane vrijednosti
int printReceipts(receiptPosition head); //funkcija koja ispisuje sve racune i artikle
int printReceiptsInRange(receiptPosition head, char dateFrom[], char dateTo[]); //funkcija koja ispisuje sve racune u odredenom vremenskom intervalu
int findTheMostExpensiveReceipt(receiptPosition head);//funkcija koja trazi najskuplji racun
int findTheCheapestReceipt(receiptPosition head); //funkcija koja trazi najjeftiniji racun
int totalMoneySpent(receiptPosition head);//funkcija koja racuna koliko se ukupno novaca potrosilo na sve racune

#endif
