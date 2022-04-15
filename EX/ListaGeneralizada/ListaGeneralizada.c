#include "ListaGeneralizada.h"
 
int main(){
    Node* l1 = concat(atom(1),concat(atom(2),NULL));
    Node* l2 = concat(subList(l1),concat(atom(4),NULL));
    Node* l3 = concat(atom(5),concat(atom(6),concat(subList(l2),concat(subList(l1),NULL))));

    show(l3); printf("\n");

    printf("//DEPTH: %d",depth(l3));
}