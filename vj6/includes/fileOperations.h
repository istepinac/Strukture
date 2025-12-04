#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
typedef struct Receipt* receiptPosition;


int createReceipts(); //funkcija koja kreira listu sa svim racunima i proizvodima iz datoteke
int countReceipts(); //funkcija koja broji koliko racuna ima u datoteci
int freeList(receiptPosition head);//funkcija za oslobadanje alocirane memorije za cijelu listu
int pauseScreen();//funkcija koja sluzi kako bi zaustavila loop dok korisnik ne pritisne ENTER - zbog citljivosti programa


#endif
