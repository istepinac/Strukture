#include "cars.h"
#include "clients.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define LOAD_FACTOR_THRESHOLD 0.7
#define INITIAL_CAR_TABLE_SIZE 50

carPos *carHash = NULL;
int carTableSize = 0;
int carCount = 0;

int initCarHash() {
    carTableSize = INITIAL_CAR_TABLE_SIZE;
    carCount = 0;

    carHash = malloc(carTableSize * sizeof(carPos));
    if (!carHash)
        return EXIT_FAILURE;

    for (int i = 0; i < carTableSize; i++)
        carHash[i] = NULL;

    return EXIT_SUCCESS;
}

double getCarLoadFactor() {
    return (double)carCount / carTableSize;
}

int rehashCar() {
    int oldSize = carTableSize;
    carPos *oldTable = carHash;

    carTableSize *= 2;
    carHash = malloc(carTableSize * sizeof(carPos));
    if (!carHash)
        return EXIT_FAILURE;

    for (int i = 0; i < carTableSize; i++)
        carHash[i] = NULL;

    carCount = 0;

    for (int i = 0; i < oldSize; i++) {
        carPos current = oldTable[i];
        while (current) {
            carPos next = current->next;
            unsigned int index = hash_string(current->registration) % carTableSize;
            current->next = carHash[index];
            carHash[index] = current;
            carCount++;
            current = next;
        }
    }

    free(oldTable);
    return EXIT_SUCCESS;
}

carPos allocateCar() {
    carPos newCar = malloc(sizeof(cars));
    if (!newCar)
        return NULL;
    return newCar;
}

carPos initCar(const char *registration, const char *VIN, const char *name,
               const char *engineType, clientPos owner) {
    carPos newCar = allocateCar();
    if (!newCar)
        return NULL;

    strcpy(newCar->registration, registration);
    strcpy(newCar->VIN, VIN);
    strcpy(newCar->name, name);
    strcpy(newCar->engineType, engineType);
    newCar->owner = owner;
    newCar->service = NULL;
    newCar->next = NULL;
    newCar->ownerNext = NULL;

    return newCar;
}

carPos addCarToHash(const char *registration, const char *VIN,
                    const char *name, const char *engineType, clientPos owner) {
    if (!registration || !owner)
        return NULL;

    if (getCarLoadFactor() >= LOAD_FACTOR_THRESHOLD)
        rehashCar();

    unsigned int index = hash_string(registration) % carTableSize;
    carPos current = carHash[index];

    while (current) {
        if (!strcmp(current->registration, registration))
            return current;
        current = current->next;
    }

    carPos newCar = initCar(registration, VIN, name, engineType, owner);
    if (!newCar)
        return NULL;

    if (!owner->cars) {
        owner->cars = newCar;
    } else {
        carPos temp = owner->cars;
        while (temp->ownerNext &&
               strcmp(temp->ownerNext->name, newCar->name) < 0)
            temp = temp->ownerNext;

        newCar->ownerNext = temp->ownerNext;
        temp->ownerNext = newCar;
    }

    newCar->next = carHash[index];
    carHash[index] = newCar;
    carCount++;

    return newCar;
}

void printCarHash() {
    for (int i = 0; i < carTableSize; i++) {
        carPos current = carHash[i];
        while (current) {
            printf("[Index %d: %s %s %s %s | %s %s %]\n",
                   i,
                   current->name,
                   current->registration,
                   current->engineType,
                   current->VIN,
                   current->owner->name,
                   current->owner->surname,
                   current->owner->phoneNum);
            printf("\n");
            current = current->next;
        }
    }
}

carPos findCarInHash(const char *registration) {
    if (!registration)
        return NULL;

    unsigned int index = hash_string(registration) % carTableSize;
    carPos current = carHash[index];

    while (current) {
        if (!strcasecmp(current->registration, registration))
            return current;
        current = current->next;
    }

    return NULL;
}

carPos findCarInHashByVIN(const char *VIN) {
    if (!VIN)
        return NULL;

    for (int i = 0; i < carTableSize; i++) {
        carPos current = carHash[i];
        while (current) {
            if (!strcasecmp(current->VIN, VIN))
                return current;
            current = current->next;
        }
    }

    return NULL;
}

carPos findClientCarByString(clientPos client, char string[]) {
    if (!client)
        return NULL;

    carPos temp = client->cars;
    while (temp &&
           strcasecmp(temp->registration, string) != 0 &&
           strcasecmp(temp->VIN, string) != 0)
        temp = temp->ownerNext;

    return temp;
}
