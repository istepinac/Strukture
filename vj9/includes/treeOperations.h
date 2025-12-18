#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


typedef struct Tree* Position;

typedef struct Tree{
    int value;
    Position leftChild,rightChild;
    
}Tree;

Position allocate();//funkcija koja alocira memoriju za novi cvor u stablu
Position init(int value);// funkcija koja inicijalizira novi cvor i postavlja value na datu vrijednost
Position addNewEl(Position root , int value);//funkcija koja dodaje novi element u stablo sa zadanom vrijednoscu
int replace(Position root);//funkcija koja svaki element stabla mijenja sa sumom elemenata lijevog i desnog podstabla
Position randGenTree();//funkcija koja generira stablo sa random brojevima
int preorderPrint(Position root, int depth);//funkcija koja ispisuje u terminal preorder stablo
int freeTree(Position root);//funkcija koja oslobadja memoriju cijelog stabla

#endif

