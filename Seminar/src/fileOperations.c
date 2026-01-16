#include "../includes/fileOperations.h"
#include "../includes/clients.h"
#include "../includes/cars.h"
#include"../includes/services.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int readFile(){
    
    FILE *file = fopen("files/klijenti.txt", "r");
    
    if (file == NULL) {
        printf("Problem pri otvaranju datoteke!\n");
        return EXIT_FAILURE;
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        char *name = strtok(buffer," ");
        char *surname = strtok(NULL," ");
        char *phoneNum = strtok(NULL," ");
        char *carPath = strtok(NULL," ");

        if (!name || !surname || !phoneNum || !carPath)
            continue;

        clientPos owner = addClientToHash(name, surname, phoneNum);

        FILE *cars = fopen(carPath,"r");
        if (cars == NULL) {
            printf("Problem pri otvaranju %s! Preskačem datoteku!\n", carPath);
            continue;
        }
        
        char carBuffer[256];
        while (fgets(carBuffer, sizeof(carBuffer), cars) != NULL) {
            carBuffer[strcspn(carBuffer, "\r\n")] = 0;

            char *carName = strtok(carBuffer, " ");
            char *registration = strtok(NULL, " ");
            char *motorType = strtok(NULL, " ");
            char *VIN = strtok(NULL, " ");
            char *serviceFile = strtok(NULL, " ");

            if (!carName || !registration || !motorType || !VIN || !serviceFile)
                continue;

            carPos car = addCarToHash(registration, VIN, carName, motorType, owner);
            if (!car) {
                printf("Error pri dodavanju automobila u hash!\n");
                continue;
            }

            FILE *servFile = fopen(serviceFile, "r");
            if (!servFile) {
                printf("Problem pri otvaranju servisnog file-a %s! Preskačem!\n", serviceFile);
                continue;
            }

            char servBuffer[512];
            while (fgets(servBuffer, sizeof(servBuffer), servFile) != NULL) {
                servBuffer[strcspn(servBuffer, "\r\n")] = 0;

                char date[12];
                int km;
                char description[256];

                if (sscanf(servBuffer, "%11s %d km %[^\n]", date, &km, description) == 3) {
                    sortAddService(car, km, date, description);
                }
            }

            fclose(servFile);
        }

        fclose(cars);
    }

    fclose(file);
    return 0;
}
