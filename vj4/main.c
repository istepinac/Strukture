/*
 Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
 čitaju iz datoteke.
 Napomena: Eksponenti u datoteci nisu nužno sortirani.
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Number* Position;
typedef struct Number{
    int coef;
    int power;
    Position next;
}Number;

int readFile(int numberOfRows, Position head[]);
Position init(); //funkcija za inicijaliziranje elemenata na vrijednosti nula i njihov pokazivac na NULL
Position allocate(); // funkcija za alociranje memorije
int countRows(); // funkcija koja broji koliko redaka odnosno polinoma sadrzi file
bool checkIfNumber(char buffer[50]); //funkcija koja provjerava je li ocitani sadrzaj filea broj
int sortInsert(Position head,Position newElement); // funkcija koja ubacuje element tako su eksponenti sortirani od najveceg prema najmanjeg
int printList(Position head); //funkcija koja ispisuje listu u formatu polinoma
int pickOperation(Position head[],int numberOfRows); //funkcija za biranje matematicke operacije
int add(Position head[],int numberOfRows); //funkcija za zbrajanje polinoma
int multiply(Position head [], int numberOfRows);//funkcija za mnozenje polinoma
int freeList(Position head);//funkcija za oslobadanje jedne liste iz memorije
Position checkIfExpExist(Position head, int power); // funkcija koja provjerava postoji li exponent u listi i vraca pokazivac na taj element


int main() {
    int numberOfRows = countRows();
    Position head[numberOfRows];
    readFile(numberOfRows, head);
    pickOperation(head, numberOfRows);
    printf("The result of the operation is \n");
    printList(head[0]);
    printf("\n");

    

    freeList(head[0]);
    return 0;
    
    
    
}
Position init(){
    Position element = allocate();
    element->coef = 0;
    element->power = 0;
    element->next=NULL;
    
    return element;
}

Position allocate(){
    Position newElement = (Position)malloc(sizeof(Number));
    if (newElement == NULL){
        printf("Error: There is no enough memory! \n");
        return NULL;
    }
    return newElement;
}

int readFile( int numberOfRows, Position head[numberOfRows]){
    FILE *file = fopen("polynoms.txt","r" );
    if(file == NULL){
        printf("Error opening file! \n");
        return EXIT_FAILURE;
    }
    if(fgetc(file)== EOF){
        printf("File is empty! \n");
        return EXIT_FAILURE;
    }
    rewind(file);
   
    char buffer[256];
    
    for (int i = 0; i<numberOfRows; i++) {
        head[i] = init();
        if (!fgets(buffer, sizeof(buffer), file)) {
            printf("Error: not enough lines in file! \n");
            break;
        }

        char *token = strtok(buffer, " \t\r\n");
            
        while (token !=  NULL) {
            if (!checkIfNumber(token)) {
                printf("Error: Coef is not a number! \n");
                fclose(file);
                return EXIT_FAILURE;
            }
            Position newElement = init();
            newElement->coef = atoi(token);
                
            token = strtok(NULL, " \t\r\n");
            if (token == NULL || !checkIfNumber(token)) {
                printf("Error: There is no exponent in line!\n");
                fclose(file);
                return EXIT_FAILURE;
            }
            newElement->power = atoi(token);
            sortInsert(head[i], newElement);
                
            token = strtok(NULL," \t\r\n");
      }
            
        
    }
   
    
    fclose(file);
    return 0;

}
int countRows(){
    FILE *file = fopen("polynoms.txt","r" );
    if(file == NULL){
        printf("Error opening file! \n");
        return EXIT_FAILURE;
    }
    if(fgetc(file)== EOF){
        printf("File is empty! \n");
        return EXIT_FAILURE;
    }
    rewind(file);
    int counter =0;
    int ch;
    while((ch = fgetc(file)) != EOF){
        if(ch =='\n')
            counter++;
    }
    fclose(file);
    return counter;
}

 bool checkIfNumber( char buffer[50]){
        if((buffer[0] == '-' && isdigit(buffer[1])) || isdigit(buffer[0])){
            return true;
        }
        else{
            return false;
        }
    }

int sortInsert(Position head,Position newElement){

    if (head->next == NULL) {
        head->next = newElement;
    }
    else{
        Position temp = head;
        while( temp->next != NULL  && (newElement->power < temp->next->power)){
            temp = temp->next;
        }
        newElement->next = temp->next;
        temp->next = newElement;
    }
    return EXIT_SUCCESS;
}

int printList(Position head){
    Position temp = head->next;
    int first = 0;
    
    while (temp != NULL){
        if(first != 0 && temp->coef > 0 ){
            printf(" + ");
        }
    
        printf("%d", temp->coef);
        if (temp->power == 0) {
            printf("");
        }
        else if (temp->power == 1){
            printf("x");
        }
        else{
            printf("x^%d",temp->power);
        }
        first = 1;
        
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int pickOperation(Position head[], int numberOfRows){
    int pick;
    printf("Do you want to add (0) or multiply (1) polynoms?\n");
    scanf("%d",&pick);
    while (pick != 0 && pick != 1) {
        printf("Invalid input, try again. \n");
        scanf("%d",&pick);
    }

    if (pick == 0) {
        add(head,numberOfRows);
    }
    else multiply(head, numberOfRows);

    
    
    return EXIT_SUCCESS;
}


int add(Position head [],int numberOfRows){
    
    for(int i = numberOfRows-1; i>0;i--){
        Position poly1 = head[i]->next;

        while (poly1 != NULL) {
            Position poly2 = head[i-1]->next;
            Position nextPoly1 = poly1->next;  // save next node

            // Traverse poly2 to find matching power or insert position
            while (poly2->next != NULL && poly2->next->power > poly1->power) {
                poly2 = poly2->next;
            }

            if (poly2->next != NULL && poly2->next->power == poly1->power) {
                poly2->next->coef += poly1->coef;
            } else {
                Position newElement = init();
                newElement ->coef = poly1->coef;
                newElement ->power = poly1 -> power;
                sortInsert(head[i-1], newElement); // insert poly1 in correct position
            }

            poly1 = nextPoly1;
        }
        freeList(head[i]);
        
        
    }
    return EXIT_SUCCESS;
}

int multiply(Position head [], int numberOfRows){
    for (int i = numberOfRows-1; i>0; i--) {
        Position result = init();
        Position poly1 = head[i]->next;
        while (poly1 != NULL) {
            Position poly2 = head[i-1]->next;
            while (poly2 != NULL) {
                Position newElement = init();
                newElement->coef = poly1->coef * poly2->coef;
                newElement->power= poly1->power + poly2 ->power;
                Position temp = checkIfExpExist(result, newElement->power);
                if(temp){
                    temp->coef += newElement->coef;
                }
                else{
                    sortInsert(result, newElement);
                }
                poly2 = poly2->next;
            }
            poly1 = poly1->next;
        }
        head[i-1]= result;
        freeList(head[i]);
        
    }
    return EXIT_SUCCESS;
}

int freeList(Position head){
    Position temp = head;
    while(temp != NULL){
        
        Position next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = next;
    }
    return EXIT_SUCCESS;
}

Position checkIfExpExist(Position head, int power){
    Position temp = head->next;
    if (temp == NULL) {
        return NULL;
    }
        while(temp!=NULL && temp->power != power){
            temp = temp->next;

        }
    return temp;
}




