/*
 Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
 a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
 sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
 pokazivač na korijen stabla.
 b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
 njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
 vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
 slici Slika 2.
 c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
 funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
 upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
 dijela zadatka.
 */

#include "../includes/treeOperations.h"
#include "../includes/fileOpeartions.h"
#include<stdio.h>
#include<ctype.h>
#include <time.h>
#include<stdlib.h>


int main(){
    srand((unsigned)time(NULL));
    
    Position root = init(0); // kreiranje dummy roota stabla
    readNumbers(root); //kreiranje cijelog stabla, i izmjena dummy roota u slucaju da korijen nije 0
    preorderPrint(root, 0); //ispis stabla radi preglednosti
    
    printf("zbroj svih elemenata je %d\n\n",replace(root));//zbrajanje svih podstabala za svaki cvor, i ispis sume cijelog stabla
    
    preorderPrint(root, 0); //ispis stabla nakon replacea radi preglednosti
    Position randRoot = randGenTree(); //kreiranje random stabla
    preorderPrint(randRoot, 0); //ispis random stabla radi preglednosti
    replace(randRoot);// zbrajanje svih podstabala za svaki cvor
    FILE *file = fopen("files/randInorderNumbers.txt", "w");//otvaranje datoteke, s obzirom da je funkcija inorderPrintToFile rekurzivna da se nebi stalno brisalo
    if (!file) { //provjera otvaranja filea
           printf("Cannot open the file\n");
           return EXIT_FAILURE;
       }
    inorderPrintToFile(randRoot, file);//funkcija koja ispisuje inorder elemente u file
    fclose(file);//zatvaranje filea
    
    freeTree(root);// oslobadanje memorije za oba stabla
    freeTree(randRoot);


    return EXIT_SUCCESS;
}
