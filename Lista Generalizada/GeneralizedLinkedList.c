#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"GeneralizedLinkedList.h"


int addAtom(No **list, int put){
	// criacao do no a ser adicionado
	No *Nodd = (No*) malloc(sizeof(No));
	Nodd->t = 0;
	Nodd->next = NULL;
	Nodd->atomList.atom = put;

	// navegacao na lista
	if(*list == NULL){
		*list = Nodd;
	}else{
		No *navg  = *list;
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
int addList(No **list, No **subList){
	// criacao do no a ser adicionado
	No *Nodd = (No*) malloc(sizeof(No));
	Nodd->t = 1;
	Nodd->next = NULL;
	Nodd->atomList.list = *subList;

	// navegacao na lista
	if(*list == NULL){
		*list = Nodd;
	}else{
		No *navg  = *list;
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
No* head(No *list){

	No *h = list;
	if(h == NULL)
	{
		return NULL;
	  }

	if(h->t==0) //atom
	{
		return h;
	}
	else{ //list
		return h->atomList.list;
	}

}
No* tail(No *list){

	No *h = list;
	h = h->next;
	return h;

}
void show(No *list){
	No *navg  = list;

	/*
	if( navg->type == 0 && navg->next == NULL){
		printf("%d", navg->atomList.atom);
		return;
	}
	*/

	while(1){
		if(navg->t == 0){
			printf(" %d ", navg->atomList.atom );
		}
		if(navg->t == 1){
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
void showMe( No *list){
	printf("(");
	show(list);
	printf(")");
}
void ln(){
	printf("\n");
}
bool search(No *list, int atom){
	No *h = list;
	if(h == NULL) return false;
	int a = 1;
	while(a){
		if(h->t == 0){ // comparando atomo
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
int depth(No *list){
	No *h = list;
	int dN = 0, a = 1, c, c2 = -1;
	if(h == NULL) return 0;

	while(a){
		// conferir na lista profundidade
		if(h->t==1){
			c = depth(h->atomList.list);
			c +1;
			if(c > c2) c2 = c;
		}
		h = h->next;


		if(h == NULL)break;
	}
	return c2+1;
}
