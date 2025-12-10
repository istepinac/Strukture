#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


typedef struct Directory* Position;
typedef struct dirPosition* Stack;

typedef struct Directory{
    char name[50];
    Position next,child;
    
}Directory;


Position allocate();//funkcija za alociranje memorije elemenata stabla
Position init(char name[]);//funkcija za inicijaliziranje vrijednosti elemenata stabla
int sortAddDirectory(Position current, char name[]);//funkcija koja abecedno sortirano unosi poddirektorije
int makeDirectory(Stack stackHead, char name[]);//funkcija koja kreira direktorij
int printChildDirectories(Stack stackHead);//funkcija koja ispisuje sve poddirektorije jednog direktorija
int cdDirectory(Stack stackHead, char name[] );//funkcija za ulazenje u neki direktorij(koji je ujedno poddirektorij trenutnog direktorija)
int freeTree(Position head);//funkcija za oslobadanje memorije cijelog stabla, napravljeno preko rekurzije
int renameDir(Position current,char oldName[], char newName[]);//funkcija koja mijenja naziv direktorija
int deleteDir(Position current,char name[]);//funkcija koja brise direktorij i sve njegove poddirektorije
Position searchForName(Position head, char name[]);//funkcija koja pretrazuje postoji li ime u listi i vraca njegovu poziciju

#endif

