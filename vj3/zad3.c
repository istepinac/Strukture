/*3. Prethodnom zadatku dodati funkcije:
 A. dinamički dodaje novi element iza određenog elementa,
 B. dinamički dodaje novi element ispred određenog elementa,
 C. sortira listu po prezimenima osoba,
 D. upisuje listu u datoteku,
 E. čita listu iz datoteke.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define INITIALIZE_ERROR -1
#define ERROR_OPENING_FILE -1


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
int createPerson(Position newPerson,char name[20], char surname[30], int birthYear); // funkcija koja pridruzuje zadane vrijednosti (ime, prezime, godinu)
int insertBeforeElement(Position head, char name[20], char surname[30], int birthYear, char elementSurname[30]); //funkcija koja dodaje element ispred nekog elementa
int insertAfterElement(Position head, char name[20], char surname[30], int birthYear, char elementSurname[30]);//funkcija koja dodaje element iza nekog elementa
int sortListBySurname(Position head); //funkcija za sortiranje elemenata po prezimenu
int countListElements(Position head); //funkcija koja broji koliko ima clanova liste
int menuPick();// funkcija koja pokazuje menu odabira i vraca odabranu vrijednost
int pauseScreen(); //funkcija koja sluzi kako bi zaustavila loop dok korisnik ne pritisne ENTER - zbog citljivosti programa
int insertListToFile(Position head); // funkcija koja upisuje vezanu listu u file
int readListFromFile(Position head); //funkcija koja ucitava listu iz datoteke



int main() {
    Position head = initHead();
    if (head == NULL) {
        printf("Init Error!\n");
        return -1;
    }

    int pick = 0;
    char name[20], surname[30], searchSurname[30], elementSurname[30];
    int birthYear;

    while (1) { //menu za biranje funkcija
        int pick = menuPick();
        switch (pick) {
        case 0:
            printf("Enter data (Name Surname BirthYear): ");
            scanf("%s %s %d", name, surname, &birthYear);
            insertAtStart(head, name, surname, birthYear);
            pauseScreen();
            break;

        case 1:
            printf("Enter data (Name Surname BirthYear): ");
            scanf("%s %s %d", name, surname, &birthYear);
            insertAtEnd(head, name, surname, birthYear);
            pauseScreen();
            break;

        case 2:
            printf("Enter surname to search: ");
            scanf("%s", searchSurname);
            {
                Position found = searchBySurname(head, searchSurname);
                if (found != NULL)
                    printf("Found: %s %s %d\n", found->name, found->surname, found->birthYear);
            }
            pauseScreen();
            break;

        case 3:
            printf("\n--- Current List ---\n");
            printList(head);
            pauseScreen();
            break;

        case 4:
            printf("Enter surname to delete: ");
            scanf("%s", surname);
            deleteElementBySurname(head, surname);
            pauseScreen();
            break;

        case 5:
            printf("Enter new person data (Name Surname BirthYear): ");
            scanf("%s %s %d", name, surname, &birthYear);
            printf("Enter surname of the element BEFORE which you want to insert: ");
            scanf("%s", elementSurname);
            insertBeforeElement(head, name, surname, birthYear, elementSurname);
            pauseScreen();

            break;

        case 6:
            printf("Enter new person data (Name Surname BirthYear): ");
            scanf("%s %s %d", name, surname, &birthYear);
            printf("Enter surname of the element AFTER which you want to insert: ");
            scanf("%s", elementSurname);
            insertAfterElement(head, name, surname, birthYear, elementSurname);
            pauseScreen();

            break;

        case 7:
            sortListBySurname(head);
            printf("List sorted by surname.\n");
            pauseScreen();
            break;
                
        case 8:
                insertListToFile(head);
                pauseScreen();
                break;
        case 9:
                readListFromFile(head);
                pauseScreen();
                break;
                
        case 10:
            printf("Exiting program...\n");
            freeList(head);
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
            break;
        }
    }

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
    while(temp != NULL  && strcasecmp(temp->surname, surname) != 0){
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
    Position temp = head->next;
    while (temp!=NULL) {
        Position next = temp->next;
        free(temp);
        temp =next;
    }
    head=initHead();
    return 0;
}

int createPerson(Position newPerson,char name[20], char surname[30], int birthYear){
    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    
    return 0;
}

int insertBeforeElement(Position head, char name[20], char surname[30], int birthYear, char elementSurname[30]){
    Position element = searchBySurname(head, elementSurname);
    Position temp = head;
    while (temp->next !=element) {
        temp=temp->next;
    }
    
    insertAtStart(temp, name, surname, birthYear);
    
    return 0;
    
}

int insertAfterElement(Position head, char name[20], char surname[30], int birthYear, char elementSurname[30]){
    Position element = searchBySurname(head, elementSurname);
    Position temp= head;
    while (temp!=element) {
        temp=temp->next;
    }
    insertAtStart(temp, name, surname, birthYear);
    return 0;
}


int sortListBySurname(Position head){
    int numberOfELements = countListElements(head);
    Position p= head;
    Position q = p->next;
    int swapped = 0;
    
    while(numberOfELements > 1){
        swapped = 0;
         p= head;
         q = p->next;
        while (q->next != NULL) {
            if (strcasecmp(q->surname,q->next->surname)>0) {
                Position temp = q;
                p->next = q->next;
                temp->next = q->next->next;
                p->next->next = temp;
                swapped = 1;
                
            }
            
            p=p->next;
            q=p->next;
            
        }
        if(swapped == 0) break;
        
        numberOfELements--;
    }
    
    return 0;
    
}

int countListElements(Position head){
    Position temp = head->next;
    int counter =0;;
    while(temp!=NULL){
        temp= temp->next;
        counter++;
    }
    return counter;
}

int menuPick(){
    int pick;
    printf("\n======================================\n");
    printf("Select the operation you want to do:\n");
    printf("0 - Insert element at start of the list\n");
    printf("1 - Insert element at the end of the list\n");
    printf("2 - Search element by surname\n");
    printf("3 - Print list\n");
    printf("4 - Delete element by surname\n");
    printf("5 - Insert before element\n");
    printf("6 - Insert after element\n");
    printf("7 - Sort list by surname\n");
    printf("8 - Insert list to file\n");
    printf("9 - Read list from file\n");
    printf("10 - Exit program\n");
    printf("======================================\n");
    printf("Enter your choice: ");
    scanf("%d", &pick);
    
    return pick;
}
int pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    return 0;
}
int insertListToFile(Position head) {
    Position temp = head->next;
    int choice;
    printf("Do you want to append (0) or overwrite (1)? ");
    scanf("%d", &choice);
    char mode[2];
    
    if (choice == 0)
        strcpy(mode, "a");
    else if (choice == 1)
        strcpy(mode, "w");
    else {
        printf("Invalid choice. Aborting.\n");
        return 0;
    }
 
        
    FILE *file = fopen("data.txt", mode);
    if (file == NULL) {
        perror("Error opening file");
        return -2;
    }

    int count = 0;
    while (temp != NULL) {
        fprintf(file, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
        count++;
    }

    fclose(file);
    printf("Wrote %d entries to data.txt\n", count);

    return 0;
}
int readListFromFile(Position head) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -2;
    }
    int choice;
    if (head->next == NULL){ //ako nam je lista prazna - ucitava odmah podatke
        choice=0;
    }
    else{
        printf("Do you want to append (0) or overwrite (1)? ");
        scanf("%d", &choice);
    }
    char name[20],surname[30];
    int birthYear;
    if (choice == 0){
        while (fscanf(file,"%s %s %d",name,surname,&birthYear)==3) {
            insertAtEnd(head,name , surname, birthYear);
        }
    }
    else if (choice == 1){
        freeList(head);
        while (fscanf(file,"%s %s %d",name,surname,&birthYear)==3) {
            insertAtEnd(head,name , surname, birthYear);
        }
    }
    else {
        printf("Invalid choice. Aborting.\n");
        return 0;
    }
    return 0;
 
}

