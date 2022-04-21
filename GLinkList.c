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
	
	Node *h = list;
	if(h == NULL)
	{
		return NULL;
	  }
	
	if(h->type==0) //atom
	{
		return h;
	}
	else{ //list
		return h->atomList.list;
	}
	
}
Node* tail(Node *list){
	
	Node *h = list;
	h = h->next;
	return h;
	
}
void show(Node *list){
	Node *navg  = list;

	/*
	if( navg->type == 0 && navg->next == NULL){
		printf("%d", navg->atomList.atom);
		return;
	}
	*/
	
	while(1){
		if(navg->type == 0){
			printf(" %d ", navg->atomList.atom );
		}
		if(navg->type == 1){
			printf("("); // Abertura
			show(navg->atomList.list);
			printf(")"); // Fechamento
			//printf(" () ");
		}
		if(navg->next == NULL){
			break;
		} else {
			printf(",");
			navg = navg->next;
		}
	}
	
	
}
void showMe( Node *list){
	printf("(");
	show(list);
	printf(")");
}
void ln(){
	printf("\n");
}
bool search(Node *list, int atom){
	Node *h = list;
	if(h == NULL) return false;
	int a = 1;
	while(a){
		if(h->type == 0){ // comparando atomo
			if(h->atomList.atom == atom) return true;
		} else { // entrnado lista
			if( search(h, atom) ){
				return true; break;
			}
		}
		h = h->next;
		if(h == NULL){
			return false;
		}
	}
}
int depth(Node *list){
	Node *h = list;
	int dN = 0, a = 1, c, c2 = -1;
	if(h == NULL) return 0;
	
	while(a){
		// conferir na lista profundidade
		if(h->type==1){
			c = depth(h->atomList.list);
			c +1;
			if(c > c2) c2 = c;
		}
		h = h->next;
		
		
		if(h == NULL)break;
	}
	return c2+1;
}