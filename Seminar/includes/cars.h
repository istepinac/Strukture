#ifndef CARS_H
#define CARS_H

#define CAR_NAME_SIZE 40

typedef struct cars* carPos;
typedef struct clients* clientPos;
typedef struct service* servicePos;

extern carPos *carHash;
extern int carTableSize;
extern int carCount;

typedef struct cars {
    char registration[15];
    char VIN[20];
    char name[CAR_NAME_SIZE];
    char engineType[15];
    carPos ownerNext;
    carPos next;
    clientPos owner;
    servicePos service;
} cars;

int initCarHash(); // Inicijalizira hash tablicu na početnu veličinu (50) i postavlja brojač na 0
double getCarLoadFactor(); // Računa omjer popunjenosti (carCount / carTableSize) za potrebe automatskog proširenja
int rehashCar(); // Dvostruko povećava veličinu tablice i preraspoređuje sve postojeće elemente u nove indekse

carPos allocateCar();// Alocira memoriju za novu strukturu automobila
carPos initCar(const char *registration, const char *VIN,
               const char *name, const char *engineType, clientPos owner);// Stvara novi čvor automobila i puni ga proslijeđenim podacima (registracija, VIN, vlasnik...)
carPos addCarToHash(const char *registration, const char *VIN,
                    const char *name, const char *engineType, clientPos owner);// Dodaje automobil u hash tablicu po registraciji; također ga sortira u vlasnikovu listu po imenu automobila

void printCarHash();// Prolazi kroz cijelu hash tablicu i ispisuje detaljne podatke o svakom automobilu i njegovom vlasniku
carPos findCarInHash(const char *registration);// Brzo pronalazi automobil koristeći hash funkciju na temelju registarske oznake
carPos findCarInHashByVIN(const char *VIN);// Pronalazi automobil linearnom pretragom kroz cijelu tablicu preko broja šasije
carPos findClientCarByString(clientPos client, char string[]);// Pronalazi određeni automobil unutar povezane liste određenog klijenta (preko registracije ili VIN-a)

#endif
