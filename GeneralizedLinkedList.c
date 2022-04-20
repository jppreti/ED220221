#include <stdio.h>
#include <stdlib.h>
#include "GeneralizedLinkedList.h"
#include "log.h"

int addAtom(Node **list, int atom) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->type = 0;
	newNode->atomList.atom = atom;
    newNode->next = NULL;

    if (*list == NULL)            //se a lista estiver vazia
        *list = newNode;    //novo nó é o primeiro
    else {
        Node *aux = *list;  //aux aponta para o primeiro

        while (aux->next != NULL){ //enquanto não for o último nó
            aux = aux->next;      //aux avança para o nó seguinte
			//printf("%d %p\n",aux->atomList.atom, aux->atomList.list);
		}
        aux->next = newNode;      //último nó aponta para o novo nó
    }
    return 1;
}

int addList(Node **list, Node **subList) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->type = 1;
	newNode->atomList.list = *subList;
    newNode->next = NULL;

    if (*list == NULL)            //se a lista estiver vazia
        *list = newNode;    //novo nó é o primeiro
    else {
        Node *aux = *list;  //aux aponta para o primeiro
        while (aux->next != NULL) //enquanto não for o último nó
            aux = aux->next;      //aux avança para o nó seguinte
        aux->next = newNode;      //último nó aponta para o novo nó
    }

    return 1;
}

int conta_atomos (Node* list) {
  if (list == NULL)
    return 0;
  else
    if (list->type == 0 || list->type == 1)
      return 1 + conta_atomos(list->next);
    else
      return  conta_atomos(list->atomList.list)
	+ conta_atomos(list->next);
}

void show(Node **list){
	Node *aux = *list;  //aux aponta para o primeiro
	printf("(");
    while (aux != NULL) {//enquanto não for o último nó
		if (aux->type == 0){
        	printf("%d,", aux->atomList.atom); 
		}else {
			printf("%d,", *aux->atomList.list); //aux avança para o nó seguinte
		}
    	aux = aux->next; 
	}
	printf(")");
	printf("\n");
}

int main() {
	log_set_level(LOG_TRACE);
	Node *list = NULL;
	addAtom(&list,5);
	//printf("%d %p\n",list->atomList.atom, list->atomList.list);
	Node *list2 = NULL;
	addAtom(&list2,3);
	addAtom(&list2,1);
	addList(&list,&list2);
	addAtom(&list,7);
	//printf("%d %d\n",list->atomList.atom, list->next->atomList.atom);
		//	( 5 , ( 3 , 1 ) , 7 )
	//		(A B A C A ( X I ) T E)
	//( A ( B ( O B R I N H A) A ( C A ( T E ) ( X I ) ) ) )
	show(&list);
	show(&list2);
}