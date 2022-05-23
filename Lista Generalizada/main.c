#include <stdio.h>
#include <stdlib.h>
#include "GeneralizedLinkedList.h"

bool compara(void *data1, void *data2) {
    int *d1 = (int*)data1;
    int *d2 = (int*)data2;

    return (*d1==*d2)?true:false;
}

int main() {
    No *nodeP = NULL;
	//nodeP->type = 1;
	int resp, put;
	put = 7;
	resp = addAtom(&nodeP, put);

	No *p=NULL;
	put = 2;
	resp = addAtom(&p, put);

	resp = addList(&nodeP, &p);
	//printf(" %d \n", nodeP->type);

	showMe(nodeP); ln();// Solução artifical

	show( head( p ) ); ln();
	show( tail( nodeP ) ); ln();
	show( head( tail( nodeP ) ) ); ln();
    printf(" %d \n", depth(nodeP));
	printf(" %d \n", depth(p));
	printf(" %i \n", search(nodeP, 7));
	printf(" %i \n", search(p, 7));
return EXIT_SUCCESS;}
