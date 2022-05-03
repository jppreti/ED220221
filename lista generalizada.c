#include "lista generalizada.h"
 
int main(){
    Node* l0 = NULL;
    Node* l1 = NULL;
    Node* l2 = NULL;
    Node* l3 = NULL;

    addAtom(&l0,1); addAtom(&l0,2);
    addAtom(&l1,2); addAtom(&l1,3); 
    addList(&l0,&l1); addAtom(&l0,4); addAtom(&l0,5);

    show(&l0); printf("\n");

    printf("//DEPTH: %d\n",depth(l0));

    head(&l0); printf("\n"); head(&l1); printf("\n");
    tail(&l1); printf("\n"); tail(&l0);
}