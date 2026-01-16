#ifndef USEROP_H
#define USEROP_H


typedef struct clients* clientPos;
typedef struct cars* carPos;

// Glavne funkcije za korisničko sučelje
int userOperations();             // Glavni izbornik (klijenti, automobili, pretraga)
int clientOperationsLoop(clientPos client); // Podizbornik za akcije nad specifičnim klijentom
int carOperationsLoop(carPos car);     // Podizbornik za akcije nad specifičnim automobilom
int pauseScreen();                // Funkcija koja pauzira ekran dok korisnik ne stisne Enter

#endif
