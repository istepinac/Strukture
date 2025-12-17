#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


typedef struct Tree* Position;

typedef struct Tree{
    int value;
    Position parent,leftChild,rightChild;
    
}Tree;

Position allocate();//funkcija koja alocira memoriju za novi cvor u stablu
Position init(int value);// funkcija koja inicijalizira novi cvor i postavlja value na datu vrijednost
Position addNewEl(Position root , int value, Position parent);//funkcija koja dodaje novi element u stablo sa zadanom vrijednoscu
Position findElement(Position root, int value);//funkcija koja trazi element u stablu po vrijednosti i vraca njegovu poziciju
int deleteElement(Position root, int value);//funkcija koja brise element iz stabla
Position findMin(Position root);//funkcija koja trazi minimalno dijete u stablu (korisno kod brisanja elemenata za naci njegovo najmanje dijete)
Position findMax(Position root);//funkcija koja trazi maksimalno dijete u stablu
int preorderPrint(Position root, int depth);//funkcija koja preorder ispisuje cijelo stablo
int postorderPrint(Position root, int depth);//funkcija koja postorder ispisuje cijelo stablo
int inorderPrint(Position root, int depth);//funkcija koja inorder ispisuje cijelo stablo
int printLevel(Position root, int level);// funkcija koja ispisuje sve čvorove na zadatom levelu
int height(Position root);//funkcija koja racuna visinu stabla
int levelOrder(Position root);//funkcija koja levelorder ispisuje cijelo stablo
int freeTree(Position root);//funkcija koja oslobada memoriju cijelog stabla
int isBalanced(Position root);//funkcija koja provjerava je li stablo balansirano

#endif

