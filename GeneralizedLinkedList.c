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
        while (aux->next != NULL){ //enquanto não for o último nó
            aux = aux->next;      //aux avança para o nó seguinte
		}
        aux->next = newNode;      //último nó aponta para o novo nó
    }
    return 1;
}

Node* head(Node **list){	
	Node *aux = *list;
	printf("(");
	if(aux->type==0){
		printf("%d", aux->atomList.atom );
	}else{
		show(&aux->atomList.list);
	}
	printf(")");
}

Node* tail(Node **list){	
	Node *aux = *list;
	printf("(");
    while (aux->next != NULL) {//enquanto não for o último nó
		if (aux->next->type == 0){
        	printf("%d", aux->next->atomList.atom); 
		}else {
			tail(&aux->next->atomList.list);
		}
    	if(aux->next == NULL){
			break;
		} else {
			printf(",");
			aux = aux->next;
		} 
	}
	printf(")");
}

void show(Node **list){
	Node *aux = *list;  //aux aponta para o primeiro
	printf("(");
    while (aux != NULL) {//enquanto não for o último nó
		if (aux->type == 0){
        	printf("%d", aux->atomList.atom); 
		}else {
			show(&aux->atomList.list);
		}
    	if(aux->next == NULL){
			break;
		} else {
			printf(",");
			aux = aux->next;
		} 
	}
	printf(")");
}

int main() {
	log_set_level(LOG_TRACE);
	Node *list = NULL;
	Node *list2 = NULL;
	addAtom(&list,1);
	addAtom(&list2,2);
	addAtom(&list2,3);
	addList(&list,&list2);
	addAtom(&list,4);
	printf("Lista 1 : ");
	show(&list);
	printf("\nLista 2 : ");
	show(&list2);
	printf("\nCabeça Lista 1 : ");
	head(&list);
	printf("\nCalda Lista 1 : ");
	tail(&list);
	printf("\nCabeça Lista 2 : ");
	head(&list2);
	printf("\nCalda Lista 2 : ");
	tail(&list2);
	//printf("\nCabeça da Calda Lista 2 : ");
	//head(tail(&list2));
	printf("\n");
}