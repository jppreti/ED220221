#include "GLinkList.h"
#include <stdlib.h>
#include <stdio.h>


int addAtom(Node **list, int put){
	// criacao do no a ser adicionado
	Node *Nodd = (Node*) malloc(sizeof(Node));
	Nodd->type = 0;
	Nodd->next = NULL;
	Nodd->atomList.atom = put;
	
	// navegacao na lista
	if(*list == NULL){
		*list = Nodd;
	}else{
		Node *navg  = *list;
		while(1){
			if(navg->next == NULL){
				navg->next = Nodd;
				return 1;
			} else {
				navg = navg->next;
			}
		}	
	}
	
}
int addList(Node **list, Node **subList){
	// criacao do no a ser adicionado
	Node *Nodd = (Node*) malloc(sizeof(Node));
	Nodd->type = 1;
	Nodd->next = NULL;
	Nodd->atomList.list = *subList;
	
	// navegacao na lista
	if(*list == NULL){
		*list = Nodd;
	}else{
		Node *navg  = *list;
		while(1){
			if(navg->next == NULL){
				navg->next = Nodd;
				return 1;
			} else {
				navg = navg->next;
			}
		}	
	}
	
}
Node* head(Node *list){
	
	h = list;
	if(h == NULL)
	{
		return;
	}
	if(h->type==0)
	{
		printf(" %d ", h->atomList.atom );
	}
	else{
		show(&h->atomList.list);
	}
	
}
Node* tail(Node *list){
	
}
void show(Node **list){
	printf("("); // Abertura
	
	Node *navg  = *list;
	while(1){
		if(navg->type == 0){
			printf(" %d ", navg->atomList.atom );
		}
		if(navg->type == 1){
			show(&navg->atomList.list);
			//printf(" () ");
		}
		if(navg->next == NULL){
			break;
		} else {
			printf(",");
			navg = navg->next;
		}
	}
	
	printf(")"); // Fechamento
}
bool search(Node *list, int atom){
	
}
int depth(Node *list){
	
}