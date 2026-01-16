#ifndef CLIENTS_H
#define CLIENTS_H

#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 10


typedef struct cars* carPos;
typedef struct clients* clientPos;


typedef struct clients {
    char name[NAME_SIZE];
    char surname[NAME_SIZE];
    char phoneNum[11];
    clientPos next;     // Pokazivač za rješavanje kolizija u hash tablici (Chaining)
    carPos cars;        // Pokazivač na glavu vezane liste klijentovih automobila
} clients;

// Globalne varijable za upravljanje hash tablicom klijenata
extern clientPos *clientHash;
extern int tableSize;
extern int clientCount;

// Implementacija djb2 hash algoritma za generiranje numeričke vrijednosti iz stringa
unsigned long hash_string(const char *str);

// Generira hash indeks spajanjem imena i prezimena (case-insensitive)
unsigned int hash(const char *name, const char *surname);

// Inicijalizira primarnu hash tablicu klijenata na početnu veličinu (50)
int initClientHash();

// Izračunava faktor popunjenosti tablice (broj_klijenata / velicina_tablice)
double getLoadFactor();

// Povećava tablicu (Rehashing) kada se prijeđe Load Factor prag kako bi se smanjile kolizije
int rehash();

// Dinamički alocira memoriju za novu strukturu klijenta
clientPos allocateClient();

// Stvara novi objekt klijenta i inicijalizira njegove podatke (ime, prezime, mobitel)
clientPos initClient(const char *name, const char *surname, const char *phoneNum);

// Dodaje klijenta u hash tablicu; provjerava duplikate i po potrebi pokreće rehash
clientPos addClientToHash(const char *name, const char *surname, const char *phoneNum);

// Ispisuje sve klijente iz tablice i listu automobila za svakog od njih
void printClientHash();

/**
 * Pronalazi klijenta po imenu i prezimenu.
 * Ako postoji više klijenata s istim imenom, traži unos broja mobitela za točnu identifikaciju.
 */
clientPos findClientInHash(const char *name, const char *surname);

// Pronalazi klijenta linearnom pretragom kroz cijelu tablicu koristeći broj mobitela (O(n))
clientPos findClientbyPhoneNumber(const char *phoneNum);

// Ispisuje sve automobile koji su povezani s određenim klijentom
int printClientCars(clientPos client);

#endif
