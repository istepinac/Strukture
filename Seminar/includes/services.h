#ifndef SERVICES_H
#define SERVICES_H

typedef struct cars* carPos;

typedef struct service* servicePos;
typedef struct service {
    char date[12];
    int km;
    char description[256];
    servicePos next;
} service;

/**
 * Ispisuje kompletnu povijest servisa za određeni automobil.
 * Prolazi kroz vezanu listu servisa od glave do kraja.
 */
int printAllServices(carPos car);

/**
 * Kreira novi zapis o servisu i umeće ga u vezanu listu automobila.
 * Umetanje je sortirano prema datumu (od starijeg prema novijem ili obrnuto, ovisno o formatu datuma).
 */
servicePos sortAddService(carPos car, int km, char date[], char description[]);

#endif
