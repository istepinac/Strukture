#include <stdio.h>
#include <stdlib.h>
#define ERROR_OPENING_FILE 1

typedef struct Student {
    char name[50];
    char surname[50];
    int score;
} Student;

int openData(); //funkcija za otvaranje datoteke, vraća broj redaka datoteke
Student* allocate(int numberOfStudents); // funkcija za alociranje memorije
int loadData(Student* students, int numberOfStudents); // funkcija za dohvaćanje podataka iz datoteke
int findBestScore(Student*, int); // funkcija koja traži najveći broj bodova među studentima
float relativeScore(int, int); // funkcija za računanje relativnog broja bodova

int main() {
    int numberOfStudents = openData();

    Student* students = allocate(numberOfStudents);
    if (students == NULL) return 2;

    loadData(students, numberOfStudents);
    int bestScore = findBestScore(students, numberOfStudents);
    

    for (int i = 0; i < numberOfStudents; i++) {
        printf("%s %s %d %.2f \n", students[i].name, students[i].surname, students[i].score, relativeScore(students[i].score, bestScore));
    }

    free(students);
    return 0;
}

int openData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int counter = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') counter++;
    }

    fclose(file);
    return counter;
}

Student* allocate(int numberOfStudents) {
    Student* students = (Student*)malloc(numberOfStudents * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    return students;
}

int loadData(Student* students, int numberOfStudents) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    for (int i = 0; i < numberOfStudents; i++) {
        fscanf(file, "%49s %49s %d", students[i].name, students[i].surname, &students[i].score);
    }

    fclose(file);
    return 0;
}
int findBestScore(Student* students, int numberOfStudents){
    int bestScore= students[0].score;
    for (int i=1; i<numberOfStudents; i++) {
        if (students[i].score > bestScore) {
            bestScore = students[i].score;
        }
        
    }
    return bestScore;
}

float relativeScore(int score, int bestScore){
    float relativeScore = ( (float )score/(float) bestScore) * 100.00;
    return relativeScore;
}
