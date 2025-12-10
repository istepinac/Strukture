/*
 7. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
 Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
 povratak u prethodni direktorij. Točnije program treba preko menija simulirati
 korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/treeOperations.h"
#include "../includes/stackOperations.h"
#include "../includes/userOperations.h"

int main(){
    Position head = init("C:");
    Stack stackHead = stackInit(NULL);
    push(stackHead, head);
    userOperations(head,stackHead);
    return 0;
}
