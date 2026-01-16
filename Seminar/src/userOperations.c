#include "../includes/userOperations.h"
#include "clients.h"
#include "cars.h"
#include "services.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int userOperations(){

    while(1){
        printf("\n--Autoservis Stepinac--\n");
        printf("-----------------------\n");
        printf("--MAIN MENU--\n");
        printf("-----------------------\n");
        printf("Odaberi opciju: \n");
        printf("|-> 1-Ispisi SVE klijente\n|-> 2-Ispisi SVE automobile\n|-> 3-Pronadji klijenta\n|-> 4-Pronadji automobil\n|-> 5-Dodaj NOVOG klijenta\n|-> 6-Izlaz iz programa\n" );
        int pick;
        int findPick;
        scanf("%d",&pick);
        char name[NAME_SIZE];
        char surname[NAME_SIZE];
        char phoneNum[11];
        char carRegistration[15];
        char VIN[18];
        switch (pick) {
            case 1:
                printClientHash();
                pauseScreen();
                break;
            case 2:
                printCarHash();
                pauseScreen();
                break;
            case 3:
                printf("Pretraga po: \n1-Imenu i prezimenu\n2-Broju mobitela\n");
                clientPos foundEl = NULL;
                carPos foundCar = NULL;
                scanf("%d",&findPick);
                    switch (findPick) {
                        case 1:
                            printf("Unesi puno ime klijenta: ");
                            scanf("%9s %9s",name,surname);

                            foundEl = findClientInHash(name,surname);
                            if(foundEl !=NULL){
                                printf("\nPronadjen klijent:\n%s %s, %s\n",foundEl->name,foundEl->surname,foundEl->phoneNum);
                                pauseScreen();
                                clientOperationsLoop(foundEl);
                            }else{
                                printf("Klijent %s %s ne postoji u tablici!\n",name,surname);
                            }
                            pauseScreen();
                            break;
                        case 2:
                            printf("Unesi broj mobitela klijenta: ");
                            scanf("%10s",phoneNum);
                            foundEl = findClientbyPhoneNumber(phoneNum);
                            if(foundEl !=NULL){
                                printf("\nPronadjen klijent:\n%s %s, %s\n",foundEl->name,foundEl->surname,foundEl->phoneNum);
                                pauseScreen();
                                clientOperationsLoop(foundEl);
                            }else{
                                printf("Klijent %s ne postoji u tablici!\n",phoneNum);
                            }
                            pauseScreen();
                            break;
                        default:
                            break;
                    }
               
                break;
            case 4:
                printf("Pretraga po: \n1-Registraciji\n2-Broju šasije\n");
                scanf("%d",&findPick);
                switch (findPick) {
                    case 1:
                        printf("Unesi registraciju traženog automobila: ");
                        scanf("%14s", carRegistration);
                        foundCar = findCarInHash(carRegistration);
                        if(foundCar !=NULL){
                            printf("\nPronadjen automobil:\n%s, %s, %s, %s\n",foundCar->name,foundCar->registration,foundCar->engineType, foundCar->VIN);
                                carOperationsLoop(foundCar);
                        }else{
                            printf("Automobil %s ne postoji u tablici!\n",carRegistration);
                        }
                        pauseScreen();
                        break;
                    case 2:
                        printf("Unesi broj šasije traženog automobila: ");
                        scanf("%17s",VIN);
                        foundCar = findCarInHashByVIN(VIN);
                        if(foundCar !=NULL){
                            printf("\nPronadjen automobil:\n%s, %s, %s, %s\n",foundCar->name,foundCar->registration,foundCar->engineType, foundCar->VIN);
                                carOperationsLoop(foundCar);
                        }else{
                            printf("Automobil %s ne postoji u tablici!\n",carRegistration);
                        }
                        pauseScreen();
                        break;
                    default:
                        break;
                }
               
                break;
            
            case 5:
                printf("Unesi puno ime klijenta: ");
                scanf("%9s %9s",name,surname);
                printf("Unesi broj mobitela: ");
                scanf("%10s",phoneNum);

                
                addClientToHash(name,surname,phoneNum);
                pauseScreen();
                break;
         
                
                
            case 6:
                return EXIT_SUCCESS;
                
           
         
                
            default:
                break;
        }
    }
}
int clientOperationsLoop(clientPos client){
    
    while(1){
        printf("\n--Autoservis Stepinac--\n");
        printf("-----------------------\n");
        printf("[%s %s, %s]\n",client->name,client->surname,client->phoneNum);
        printf("-----------------------\n");
        printf("Odaberi opciju: \n");
        printf("|-> 1-Ispisi sve automobile koje %s posjeduje \n|-> 2-Pronadji automobil\n|-> 3-Dodaj novi automobil\n|-> 4-nazad\n",client->name);
        int pick;
        scanf("%d",&pick);
        char carRegistration[15];
        char VIN[18];
        char carName[CAR_NAME_SIZE];
        char engineType[15];
        
        switch (pick) {
            case 1:
                printClientCars(client);
                break;
            case 2:
                printf("Pretraga po: \n1-registraciji\n2-broju šasije\n");
                int findPick;
                carPos foundCar = NULL;
                scanf("%d",&findPick);
                    switch (findPick) {
                        case 1:
                            printf("Unesi registraciju: ");
                            scanf("%14s",carRegistration);
                           foundCar =  findClientCarByString(client, carRegistration);
                            if (foundCar != NULL) {
                                carOperationsLoop(foundCar);
                            }
                            else printf("Vlasnik %s ne posjeduje automobil s registracijom %s", client->name, carRegistration);
                            pauseScreen();
                            break;
                            
                        case 2:
                            printf("Unesi broj šasije: ");
                            scanf("%17s",VIN);
                            foundCar= findClientCarByString(client,VIN);
                            if (foundCar != NULL) {
                                carOperationsLoop(foundCar);
                            }
                            else printf("Vlasnik %s ne posjeduje automobil s brojem šasije %s", client->name, VIN);
                            pauseScreen();
                            break;
                        default:
                            break;
                    }

                break;
            case 3:
                printf("Unesi naziv automobila: (npr. BMW_320)");
                scanf("%39s",carName);
                printf("Unesi registraciju automobila: (npr. ST-123-AA) ");
                scanf("%14s",carRegistration);
                printf("Unesi broj šasije: (17 znakova)");
                scanf("%17s",VIN);
                printf("\nUnesi tip motora: (npr. 2.0D)");
                scanf("%14s",engineType);
                addCarToHash(carRegistration, VIN, carName, engineType, client);
                pauseScreen();
                break;
                
            case 4:
                printf("\nNazad...");
                return EXIT_SUCCESS;
        }
        
    }
        
}

int carOperationsLoop(carPos car){
    
    while(1){
        printf("\n--Autoservis Stepinac--\n");
        printf("-----------------------\n");
        printf("[%s, %s, %s, %s |%s %s]\n",car->name,car->registration,car->engineType,car->VIN,car->owner->name,car->owner->surname);
        printf("-----------------------\n");
        printf("Odaberi opciju: \n");
        printf("|-> 1-Ispisi sve servise \n|-> 2-Dodaj servis \n|-> 3-Pronadji vlasnika\n|-> 4-Nazad\n");
        int pick;
        scanf("%d",&pick);
        char description[256];
        int km;
        char date[12];
        
        
        switch (pick) {
            case 1:
                printAllServices(car);
                pauseScreen();
                break;
            case 2:

                printf("Unesi datum servisa (YYYY-MM-DD): ");
                scanf("%11s", date);

                printf("Unesi broj prijeđenih kilometara automobila: ");
                scanf("%d", &km);

                getchar();

                printf("Napiši opis odrađenog posla: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;

                sortAddService(car, km, date, description);
                pauseScreen();
                break;
            case 3:
                clientOperationsLoop(car->owner);
                break;
          
            case 4:
                printf("\nNazad...");
                return EXIT_SUCCESS;
        }
        
    }
        
}


int pauseScreen() {
    printf("\nPritisni Enter za nastavak...");
    getchar();
    getchar();
    return 0;
}
