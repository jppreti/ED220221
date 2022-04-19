#include <stdlib.h>
#include <stdio.h>
#include "GLinkList.h"

bool compara(void *data1, void *data2) {
    int *d1 = (int*)data1;
    int *d2 = (int*)data2;
    
    return (*d1==*d2)?true:false;
}

int main() {
    Node *nodeP = NULL;
	int resp, put;
	put = 70;
	resp = addAtom(&nodeP, put);
	
	Node *p=NULL;
	resp = addAtom(&p, put);
	
	resp = addList(&nodeP, &p);
	show(&nodeP);
	head
	
    //printf("%d\n",*((int*)dequeue(&stack)));
    
    return EXIT_SUCCESS;
}