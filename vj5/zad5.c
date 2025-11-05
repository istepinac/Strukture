/*Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Number* Position;
typedef struct Number{
    double number;
    Position next;
}Number;

Position init(); //funkcija za inicijaliziranje novog elementa na 0
Position allocate(); //fucnkija za alociranje memorije
int pop(Position head); //funkcija za brisanje zadnje dodanog elementa
int push(Position head, double number); //funkcija za dodavanje novog elementa
int calculate(Position head, char buffer); //funkcija za racunanje operacija
int readFile(Position head);//funkcija za citanje podataka iz datoteke
int printResult(Position head);//funkcija za ispis rezultata
int freeStack(Position head);//funkcija za oslobadanje memorije cijelog stoga

int main() {
    Position head = init();
    readFile(head);
    printResult(head);
    freeStack(head);
    
    return 0;
}

Position init(){
    Position element = allocate();
    element->number = 0;
    element->next = NULL;
    return element;
}
Position allocate(){
    Position newElement = (Position)malloc(sizeof(Number));
    if(newElement==NULL){
        printf("No enough memory!\n");
        return NULL;
    }
    else{
        return newElement;
    }
    
}
int push(Position head, double number){
    Position newElement = init();
    if(!newElement) return EXIT_FAILURE;
    
    newElement->number = number;

    
    newElement->next= head->next;
    head->next = newElement;
    
    
    return EXIT_SUCCESS;;
}

int pop(Position head){
    Position temp = head->next;
    if (temp == NULL) {
        printf("Error attempt to pop from empty stack. \n");
        return EXIT_FAILURE;
    }
    
    
    head->next = temp->next;
    temp->next = NULL;
    free(temp);
    return EXIT_SUCCESS;
}

int readFile(Position head){
    FILE* file = fopen("data.txt", "r");
    if(file == NULL){
        printf("Error opening file! \n");
        exit(EXIT_FAILURE);
    }
    if(fgetc(file)==EOF){
        printf("The file is empty! \n");
        exit(EXIT_FAILURE);
    }
    rewind(file);
    char buffer[100];
    
    while (fscanf(file,"%s",buffer) != EOF){
        if((buffer[0]== '-' && isdigit(buffer[1]))||isdigit(buffer[0])){
            double broj = atof(buffer); // atoi funkcija pretvara iz ascii u integer
            push(head, broj);
        }
        else{
            if(head->next == NULL){
                printf("Postfix isn't correct! \n");
                return EXIT_FAILURE;
                }
            else if(strlen(buffer)==1 && strchr("+-*/",buffer[0])){
                calculate(head, buffer[0]);
            }
            else{
                printf("Invalid character '%s' in postfix.\n", buffer);
                    exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
int calculate(Position head, char buffer){
    Position temp = head->next;
    if(temp == NULL || temp->next ==NULL){
        printf("Not enoguh operands for oporator %c .\n",buffer);
        exit(EXIT_FAILURE);
    }
    switch (buffer) {
        case '+':
            temp->next->number = temp->next->number + temp->number;
            pop(head);
            break;
        case '-':
            temp->next->number = temp->next->number - temp->number;
            pop(head);
            break;
        case '*':
            temp->next->number = temp->next->number * temp->number;
            pop(head);
            break;
        case '/':
            if(temp->number == 0){
                printf("It is not possible to divide with 0! ");
                exit(EXIT_FAILURE);
            }
            else{
                temp->next->number = temp->next->number / temp->number;
                pop(head);
                break;
            }
            
        default:
            printf("Unknown operator! \n");
            exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int printResult(Position head){
    if (head->next ==NULL) {
        printf("Stack is empty! No result.\n");
        return EXIT_FAILURE;
    }
    if (head->next->next != NULL) {
        printf("Too many operands in postfix expression.\n");
        return EXIT_FAILURE;
    }
    
    printf("Result of the task is: %.2f\n",head->next->number);
    return EXIT_SUCCESS;
}

int freeStack(Position head){
    Position temp = head;
    while(temp != NULL){
        Position next = temp->next;
        temp->next = NULL;
        free(temp);
        temp=next;
    }
    return EXIT_SUCCESS;
}
