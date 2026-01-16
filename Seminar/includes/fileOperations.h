#ifndef FILE_OP_H
#define FILE_OP_H

/**
 * Glavna funkcija za učitavanje baze podataka iz tekstualnih datoteka.
 * * Proces učitavanja je hijerarhijski:
 * 1. Otvara glavnu datoteku s klijentima (files/klijenti.txt).
 * 2. Za svakog klijenta stvara čvor u hash tablici i dohvaća putanju do datoteke s njegovim automobilima.
 * 3. Otvara datoteku s automobilima klijenta, dodaje svaki auto u hash tablicu i povezuje ga s vlasnikom.
 * 4. Za svaki automobil otvara njegovu povijest servisa i popunjava listu servisa (sortirano).
 */

int readFile();

#endif
