#include "cars.h"
#include "clients.h"
#include "../includes/fileOperations.h"
#include "../includes/userOperations.h"

#include <stdlib.h>
#include <stdio.h>

int main(){
    initClientHash();
    initCarHash();
    readFile();
    userOperations();
    return EXIT_SUCCESS;
}
