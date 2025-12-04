#ifndef ITEMS_OPERATIONS_H
#define ITEMS_OPERATIONS_H
#define MAX_NAME 30

typedef struct Receipt* receiptPosition;
typedef struct Item* itemPosition;
typedef struct Item {
    char name[MAX_NAME];
    int quantity;
    double price;
    
    itemPosition next;
    
} Item;


itemPosition itemAllocate(); //funkcija koja alocira memoriju za artikle
itemPosition itemInit(); //funkcija koja postavlja vrijednosti artikla na 0/NULL
itemPosition setItemValues(char name[],int quantity, double price);//funkcija koja postavlja vrijednosti artikla na zadane vrijednosti
int addItemToReceipt(receiptPosition receipt, char name[], int quantity, double price); //funckcija koja sortirano dodaje artikal na racun
int countItemCostInDateRange(receiptPosition head, char name[], char dateFrom[], char dateTo[]);//funkcija koja za trazeni artikal racuna koliko puta je kupljen i koliko se potrosilo novaca na njega u odredenom vremenskom intervalu
int userOperations(receiptPosition head); //funkcija koja omogucuje korisniku odabir operacija nad listom


#endif
