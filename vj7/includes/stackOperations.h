#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

typedef struct Directory* Position;

typedef struct dirPosition* Stack;
typedef struct dirPosition {
    Position dir;
    Stack next;
} dirPosition;

int push(Stack head, Position dir); //funkcija za dodavanje elemenata na stog, sluzi kako bismo znali u kojem se direktoriju nalazimo
int pop(Stack head);//funkcija za izbacivanje elemenata iz stoga
Stack stackAllocate();//funkcija za alociranje memorije elemenata stoga
Stack stackInit(Position dir);//fucnkija koja inicijalizira vrijednosti stog elementa
int freeStack(Stack stackHead);//funckija za oslobadanje memorije cijelog stoga

#endif


