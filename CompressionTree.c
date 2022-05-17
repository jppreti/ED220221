#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

// Quais carcateres presentes
// Fazer frequencia de cada caractere
// Fazer lista de caracteres por onde de maior incidencia
// juntando os menores, mantendo a ordem pós soma.

typedef struct Node {
    char* w;
    struct Node* right;
	struct Node* left;
	int f;
}Node;

typedef struct list {
	struct list* next;
	struct Node* nucleo;
}list;

void add(list **lista, char *c){
	//log_trace("Entrando no 'add'");
	// criacao do no a ser adicionado
	list *anchor = *lista;
	//log_trace("Ancora criada");
	// Node vazio
	Node *Nodd = (Node*) malloc(sizeof(Node));
	Nodd->right = NULL;
	Nodd->left = NULL;
	Nodd->f = 0;
	Nodd->w = NULL;
	log_trace("Nodd Criado");
	// navegacao na lista
	if(anchor == NULL){
		//log_trace("Ancora vazia");
		// gravando
		*lista = malloc(sizeof(list));
		Nodd->f = 1;
		Nodd->w = c;
		(*lista)->nucleo = Nodd;
		(*lista)->next = NULL;
		//log_trace("/Ancora vazia");
	}else{
		while(1){
			if(*(anchor->nucleo->w) == *c){
				//log_trace("Somando 1");
				anchor->nucleo->f += 1;
				break;
			}else if(anchor->next == NULL){
				//log_trace("adicionando node na lista");
				list *l = (list*) malloc(sizeof(list));
				anchor->next = l;
				l->nucleo = Nodd;
				l->nucleo->w = c;
				l->nucleo->f = 1;
				l->next = NULL;
				break;
			} else {
				//log_trace("Ancora->proximo");
				anchor = anchor->next;
			}
		}	
	}
return;}

void exb(list *lista){
	list *l = lista;
	while(l != NULL){
		//log_trace("Print do nucleo");
		printf("( %s, %d )\n", l->nucleo->w, l->nucleo->f);
		l = l->next;
	}
}

void org(list *lista){ // organiza a lista, colocando os nucleos com maior frequencia na cabeça e os de menor na cauda
	//log_trace("ORG");
	list *l = lista;
	list *navg;
	Node *n;
	//log_trace("NAV");
	while(l != NULL){
		navg = l->next;
		while(navg != NULL){
			if(l->nucleo->f < navg->nucleo->f){
				n = l->nucleo;
				l->nucleo = navg->nucleo;
				navg->nucleo = n;
			}
			navg = navg->next;
		}
		l = l->next;
	}
}

void mesclar(list *lista){ // organiza a lista, colocando os nucleos com maior frequencia na cabeça e os de menor na cauda
	//printf("a");
	//log_trace("ORG");
	list *l = lista;
	
		
	if (l == NULL) return;
		
	while (l->next->next != NULL ){
		l= l->next;
	}
	
	
	Node *a = (Node*) malloc(sizeof(Node));
	a->right = l->nucleo;
	a->left = l->next->nucleo;
	a->f = a->right->f + a->left->f;
	char c[50];
	strcat(c, a->right->w);
	strcat(c, a->left->w);
	strcpy(a->w, c);
	
	l->nucleo= a;
	
	free(l->next);
	l->next = NULL;

return;}



void arvore(Node *center, char *c, char *lr){
	log_trace("arv");
	strcat(c, lr); // contatear strings
	log_trace("contatear");
	if(center->right != NULL){ // caso tiver algo a direita aplique nele
		log_trace("rigt");
		arvore( center->right, c, "0");
	} 
	if (center->left != NULL){ // caso estiver algo a esquerda aplique nele 
		log_trace("left");
		arvore( center->left, c, "1");
	} else if(center->right == NULL){ // caso seja uma folha e nãto esteja apontando para mais ninguem. exiba!
		log_trace("print");
		printf("[ %s por: %s ]", center->w, c );
	} 
	
return;}

void main () {
	log_set_level(LOG_INFO);
	// Ler um arquivo
	
	FILE *arq;
	arq = fopen ("words.txt", "r");
	// para a exvição do programa {teste}
	Node *n = NULL;
	
	// criando uma lista de organizacao
	list *l = NULL;
	//(list*) malloc(sizeof(list));
	
	//l->next = NULL;
	//log_trace("Lendo arquivo");
	// do programa que copiei / editado
	int c;
	while(1) {
		c = fgetc(arq);
    	if( feof(arq) )break;
		log_trace("Converter int para char");
		char *w = malloc(sizeof(char));
		*w = c;
		add(&l, w);
		printf("%c", c);
	}printf("\n");
	fclose(arq);
	
	//exb(l);
	//printf("\n");
	//org(l);
	//exb(l);
	log_trace("arv");
	
	exb(l);
	org(l);
	mesclar(l);
	printf("\n\n");exb(l);
	org(l);
	mesclar(l);
	printf("\n\n");exb(l);
	org(l);
	mesclar(l);
	printf("\n\n");exb(l);
	//char w[] = "", ls[] = ""; 
	//arvore(l->nucleo, w, ls);
	///int fgetc(FILE *stream)
	
	
	
}