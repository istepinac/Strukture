#include "clients.h"
#include "cars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define LOAD_FACTOR_THRESHOLD 0.7
#define INITIAL_TABLE_SIZE 50

clientPos *clientHash = NULL;
int tableSize = 0;
int clientCount = 0;

unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

unsigned int hash(const char *name, const char *surname) {
    char key[30];
    snprintf(key, sizeof(key), "%s%s", name, surname);
    for (int i = 0; key[i]; i++)
        if (key[i] >= 'A' && key[i] <= 'Z')
            key[i] += 32;
    return hash_string(key) % tableSize;
}

int initClientHash() {
    tableSize = INITIAL_TABLE_SIZE;
    clientCount = 0;
    clientHash = malloc(tableSize * sizeof(clientPos));
    if (!clientHash)
        return EXIT_FAILURE;
    for (int i = 0; i < tableSize; i++)
        clientHash[i] = NULL;
    return EXIT_SUCCESS;
}

double getLoadFactor() {
    return (double)clientCount / tableSize;
}

int rehash() {
    int oldSize = tableSize;
    clientPos *oldTable = clientHash;

    tableSize *= 2;
    clientHash = malloc(tableSize * sizeof(clientPos));
    if (!clientHash)
        return EXIT_FAILURE;

    for (int i = 0; i < tableSize; i++)
        clientHash[i] = NULL;

    clientCount = 0;

    for (int i = 0; i < oldSize; i++) {
        clientPos current = oldTable[i];
        while (current) {
            clientPos next = current->next;
            unsigned int index = hash(current->name, current->surname);
            current->next = clientHash[index];
            clientHash[index] = current;
            clientCount++;
            current = next;
        }
    }

    free(oldTable);
    return EXIT_SUCCESS;
}

clientPos allocateClient() {
    clientPos newElement = malloc(sizeof(clients));
    if (!newElement)
        return NULL;
    return newElement;
}

clientPos initClient(const char *name, const char *surname, const char *phoneNum) {
    clientPos newElement = allocateClient();
    if (!newElement)
        return NULL;
    strcpy(newElement->name, name);
    strcpy(newElement->surname, surname);
    strcpy(newElement->phoneNum, phoneNum);
    newElement->cars = NULL;
    newElement->next = NULL;
    return newElement;
}

clientPos addClientToHash(const char *name, const char *surname, const char *phoneNum) {
    if (!name || !surname || !phoneNum)
        return NULL;

    if (getLoadFactor() >= LOAD_FACTOR_THRESHOLD)
        rehash();

    unsigned int index = hash(name, surname);
    clientPos current = clientHash[index];

    while (current) {
        if (!strcmp(current->name, name) &&
            !strcmp(current->surname, surname) &&
            !strcmp(current->phoneNum, phoneNum))
            return NULL;
        current = current->next;
    }

    clientPos newClient = initClient(name, surname, phoneNum);
    if (!newClient)
        return NULL;

    newClient->next = clientHash[index];
    clientHash[index] = newClient;
    clientCount++;
    return newClient;
}

clientPos findClientInHash(const char *name, const char *surname) {
    if (!name || !surname)
        return NULL;

    unsigned int index = hash(name, surname);
    clientPos current = clientHash[index];

    clientPos firstMatch = NULL;
    int matchCount = 0;

    while (current) {
        if (!strcasecmp(current->name, name) &&
            !strcasecmp(current->surname, surname)) {
            if (matchCount == 0)
                firstMatch = current;
            matchCount++;
        }
        current = current->next;
    }

    if (matchCount == 0)
        return NULL;

    if (matchCount == 1)
        return firstMatch;

    char phoneNum[11];
    scanf("%10s", phoneNum);

    current = clientHash[index];
    while (current) {
        if (!strcasecmp(current->name, name) &&
            !strcasecmp(current->surname, surname) &&
            !strcmp(current->phoneNum, phoneNum))
            return current;
        current = current->next;
    }

    return NULL;
}

clientPos findClientbyPhoneNumber(const char *phoneNum) {
    if (!phoneNum)
        return NULL;

    for (int i = 0; i < tableSize; i++) {
        clientPos current = clientHash[i];
        while (current) {
            if (!strcmp(current->phoneNum, phoneNum))
                return current;
            current = current->next;
        }
    }
    return NULL;
}

void printClientHash() {
    for (int i = 0; i < tableSize; i++) {
        clientPos current = clientHash[i];
        while (current) {
            printf("[%d: %s %s %s]\n",
                   i,
                   current->name,
                   current->surname,
                   current->phoneNum);
            carPos temp = current->cars;
            while (temp) {
                printf("  |->%s %s %s\n",
                       temp->name,
                       temp->registration,
                       temp->VIN);
                temp = temp->ownerNext;
            }
            printf("\n");
            current = current->next;
        }
    }
}

int printClientCars(clientPos client) {
    if (!client)
        return EXIT_SUCCESS;

    carPos temp = client->cars;
    while (temp) {
        printf("-> %s %s %s %s\n",
               temp->name,
               temp->registration,
               temp->engineType,
               temp->VIN);
        temp = temp->ownerNext;
    }
    return EXIT_SUCCESS;
}
