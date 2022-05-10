#include <stdio.h>
#include <stdlib.h>
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
	log_trace("Entrando no 'add'");
	// criacao do no a ser adicionado
	list *anchor = *lista;
	log_trace("Ancora criada");
	// Node vazio
	Node *Nodd = (Node*) malloc(sizeof(Node));
	Nodd->right = NULL;
	Nodd->left = NULL;
	Nodd->f = 0;
	Nodd->w = NULL;
	log_trace("Nodd Criado");
	// navegacao na lista
	if(anchor == NULL){
		log_trace("Ancora vazia");
		// gravando
		anchor = (list*) malloc(sizeof(list));
		Nodd->f = 1;
		Nodd->w = c;
		anchor->nucleo = Nodd;
		anchor->next = NULL;
		log_trace("/Ancora vazia");
	}else{
		while(1){
			if(anchor->nucleo->w == c){
				log_trace("Somando 1");
				anchor->nucleo->f += 1;
				break;
			}else if(anchor->next == NULL){
				log_trace("adicionando node na lista");
				list *l = (list*) malloc(sizeof(list));
				l->nucleo = Nodd;
				l->nucleo->w = c;
				l->nucleo->f = 1;
				l->next = NULL;
			} else {
				log_trace("Ancora->proximo");
				anchor = anchor->next;
			}
		}	
	}
return;}

void exb(list *lista){
	list *l = (list*) malloc(sizeof(list));
	l = lista;
	while(1){
		if(l == NULL){
			printf("FIM");
			break;
		}else{
			log_trace("Print do nucleo");
			printf("%s, %d", l->nucleo->w, l->nucleo->f);
		}
	}
return;}


void main () {
	log_set_level(LOG_TRACE);
	// Ler um arquivo
	
	FILE *arq;
	arq = fopen ("words.txt", "r");
	// para a exvição do programa {teste}
	Node *n = NULL;
	
	// criando uma lista de organizacao
	list *l = NULL;
	//(list*) malloc(sizeof(list));
	
	//l->next = NULL;
	log_trace("Lendo arquivo");
	// do programa que copiei / editado
	int c;
	while(1) {
		c = fgetc(arq);
    	if( feof(arq) )break;
		log_trace("Converter int para char");
		char w = c;
		add(&l, &w);
		printf("%c", c);
	}
	fclose(arq);
	
	exb(l);
	///int fgetc(FILE *stream)
	
	
	
}