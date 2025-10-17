/*Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
 A. dinamički dodaje novi element na početak liste,
 B. ispisuje listu,
 C. dinamički dodaje novi element na kraj liste,
 D. pronalazi element u listi (po prezimenu),
 E. briše određeni element iz liste,
 U zadatku se ne smiju koristiti globalne varijable.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define INITIALIZE_ERROR -1

typedef struct Person* Position;
typedef struct Person {
    char name[20];
    char surname[30];
    int birthYear;
    Position next;
} Person;

Position allocate(); // Funkcija koja samo alocira memoriju i vraca pokazivac
Position initHead(); // Funkcija koja kreira head (prazni pocetni element)
int insertAtStart(Position head, char name[20], char surname[30], int birthYear);//Funkcija za dodavanje elementa na pocetak liste
int insertAtEnd(Position head, char name[20], char surname[30], int birthYear);//Funkcija za dodavanje elementa na kraj funkcije
Position searchBySurname(Position head, char surname[30]);//Funkcija koja pretrazuje element po prezimenu
int printList(Position head);//funkcija koja ispisuje listu
int deleteElementBySurname(Position head, char surname[30]); //funkcija koja brise element u ovisnosti o prezimenu
int freeList(Position head);//funkcija za oslobadanje alocirane memorije za cijelu listu
int createPerson(Position newPerson,char name[20], char surname[30], int birthYear);

int main() {
    Position head = initHead();
    if (head == NULL) {
        printf("Init Error!\n");
        return -1;
    }
    
    insertAtStart(head, "Ivan", "Stepinac", 2005);
    insertAtStart(head, "Mate", "Matić", 2000);
    insertAtStart(head, "Jure", "Jurić", 1995);
    insertAtEnd(head, "Ivo", "Ivić",2010);
    printList(head);
    deleteElementBySurname(head, "Antić"); //Pokusaj za element koji ne postoji
    printf("\nList after 1st delete: \n \n");
    printList(head);
    deleteElementBySurname(head,"Stepinac" );
    printf("\nList after 2nd delete: \n \n");
    printList(head);
    


    freeList(head);
    return 0;
}


Position allocate() {
    Position newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("No enough memory!\n");
        return NULL;
    }
    return newPerson;
}

Position initHead() {
    Position newPerson = allocate();
    if (newPerson== NULL)
        return NULL;
    
    strcpy(newPerson->name, "");
    strcpy(newPerson->surname, "");
    newPerson->birthYear = 0;
    newPerson->next = NULL;

    return newPerson;
}

int insertAtStart(Position head, char name[20], char surname[30], int birthYear){
   Position newPerson= allocate();
    
    createPerson(newPerson,name,surname,birthYear);

    newPerson->next = head->next;
    head->next=newPerson;
    
    return 0;
}

int insertAtEnd(Position head, char name[20], char surname[30], int birthYear){
    Position newPerson= allocate();
    Position temp=head;
    while(temp->next != NULL){
        temp=temp->next;
    }
    createPerson(newPerson,name,surname,birthYear);

    temp->next = newPerson;
    newPerson->next = NULL;
    return 0;
}

int printList(Position head) {
    Position temp = head->next;
    while(temp != NULL){
        printf("%s %s %d \n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }
    return 0;
}

Position searchBySurname(Position head, char surname[30]){
    Position temp = head->next;
    while(temp != NULL  && strcmp(temp->surname, surname) != 0){
        temp=temp->next;
    }
    if(temp==NULL){
        printf("\nSearched surname doesnt exist in list! \n ");
        return NULL;
    }
    else{
        return temp;
    }
    
}

int deleteElementBySurname(Position head, char surname[30]){
    Position element= searchBySurname(head, surname);
    Position temp = head;
    if(element == NULL){
        printf("\nElement was not deleted because surname doesnt exist in list! \n ");

        return 0;
    }
    else{
        while (temp->next != element) {
            temp= temp->next;
        }
        temp->next = element->next;
        element ->next = NULL;
        free(element);
    }
    
    return 0;
}
int freeList(Position head){
    Position temp = head;
    while (temp!=NULL) {
        Position next = temp->next;
        free(temp);
        temp =next;
    }
    return 0;
}

int createPerson(Position newPerson,char name[20], char surname[30], int birthYear){
    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    
    return 0;
}


