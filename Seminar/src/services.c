#include "cars.h"
#include "clients.h"
#include "services.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int printAllServices(carPos car){
    servicePos temp = car->service;
    if(temp == NULL){
        printf("Automobil %s nema nijedan zabilježen servis! \n", car->name);
        return EXIT_SUCCESS;
    }
    while (temp != NULL) {
        printf("|-> %s %dkm %s\n",temp->date,temp->km,temp->description);
        temp=temp->next;
    }
    
    return EXIT_SUCCESS;
}

servicePos sortAddService(carPos car, int km, char date[], char description[]) {
    if (!car || !date || !description)
        return NULL;

    servicePos newService = (servicePos)malloc(sizeof(struct service));
    if (!newService)
        return NULL;

    strcpy(newService->date, date);
    newService->km = km;
    strcpy(newService->description, description);
    newService->next = NULL;

    if (car->service == NULL || strcmp(date, car->service->date) < 0) {
        newService->next = car->service;
        car->service = newService;
        return newService;
    }

    servicePos current = car->service;
    while (current->next != NULL &&
           strcmp(current->next->date, date) < 0) {
        current = current->next;
    }

    newService->next = current->next;
    current->next = newService;

    return newService;
}
