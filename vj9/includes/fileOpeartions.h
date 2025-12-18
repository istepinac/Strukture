#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>
#include <ctype.h>
int readNumbers(Position root);//funkcija koja cita zadane brojeve iz datoteke te kreira stablo s tim brojevima
int inorderPrintToFile(Position root, FILE* file);//funkcija koja inorder ispisuje stablo u datoteku


#endif

