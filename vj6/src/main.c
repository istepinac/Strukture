/*6. Napisati program koji čita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini račun. Na početku svake datoteke je zapisan datum u kojem vremenu je
račun izdat u formatu YYYY-MM-DD. Svaki sljedeći red u datoteci predstavlja artikl u formatu
naziv, količina, cijena. Potrebno je formirati vezanu listu računa sortiranu po datumu. Svaki čvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je
omogućiti upit kojim će korisnik saznati koliko je novaca sveukupno potrošeno na specifični
artikl u određenom vremenskom razdoblju i u kojoj je količini isti kupljen.*/
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

