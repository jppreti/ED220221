#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "log.h"

// Quais carcateres presentes
// Fazer frequencia de cada caractere
// Fazer lista de caracteres por onde de maior incidencia
// juntando os menores, mantendo a ordem pós soma.

typedef struct Node {
    //char* w;
	int* w;
    struct Node* right;
	struct Node* left;
	int f, g;
}Node;

typedef struct list {
	struct list* next;
	struct Node* nucleo;
}list;

void add(list **lista, int c){
		
	//printf("< %p %p >\n", lista, *lista);
	if((*lista) == NULL){ // caso for o primeiro item
		// Node vazio
		Node *Nodd = (Node*) malloc(sizeof(Node));
		Nodd->right = NULL;
		Nodd->left = NULL;
		Nodd->f = 1;Nodd->g = 1;
		Nodd->w = (int*)malloc(sizeof(int));
		(Nodd->w)[0] = c;
		
		(*lista) = malloc(sizeof(list));
		(*lista)->nucleo = Nodd;
		(*lista)->next = NULL;
	return;}
	
	list *l = *lista;
	
	if( ( *( l->nucleo->w) ) == c){
			l->nucleo->f += 1;
	return;}
	
add(&(l->next),c);}


void exb(list *lista){
	printf("\n");
	list *l = lista;
	while(l != NULL){
		//log_trace("Print do nucleo");
		
		printf("([ ");
		int a, b = l->nucleo->g; // b = 2?
		b;
		for(a=0; a<b; a++){
			//if((l->nucleo->w)[a] >= 0) 
			printf("%c ",(l->nucleo->w)[a]);
		}
		printf("], %d )",l->nucleo->f);
		//printf(" %d, ", , );
		l = l->next;
	}
printf("\n");
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
				// troca de nucleo por frequencia
				n = l->nucleo;
				l->nucleo = navg->nucleo;
				navg->nucleo = n;
			}
			if(l->nucleo->g < navg->nucleo->g){ 
			if(l->nucleo->f == navg->nucleo->f){ 
				// troca de nucleo por tamanho
				n = l->nucleo;
				l->nucleo = navg->nucleo;
				navg->nucleo = n;
			}}	
			navg = navg->next;
		}
		l = l->next;
	}
//exb(lista);
}

void mesclar(list *lista){ // organiza a lista, colocando os nucleos com maior frequencia na cabeça e os de menor na cauda
	//printf("a");
	//log_trace("ORG");
	list *l = lista;
	
		
	if (l == NULL) return;
		
	while (l->next->next != NULL ){
		l= l->next;
	}
	
	
	Node *a = (Node*) malloc(sizeof(Node)); // Criando o novo núcelo.
	a->right = l->nucleo;  // sua direita
	a->left = l->next->nucleo; // sua esquerda
	a->f = a->right->f + a->left->f; // sua frequencia
	

	printf("\n\n < %ls | %d > [ %ls | %d ]\n",a->right->w, *(a->right->w), a->left->w, *(a->left->w));
	
	int x = a->right->g;
	int y = a->left->g;
	a->g = x+y;
	int i, z[y+x]; printf("%d  %d\n", x, y);
	for ( i = 0; i<x; i++){
		z[i] = (a->right->w)[i];
	}
	for ( i = 0; i<y; i++){
		z[i+x] = (a->left->w)[i];
	}
	(a->w) = (int*) malloc((x+y)*sizeof(int));
	for( i = 0; i < x+y; i++) (a->w)[i] = z[i];
	
	l->nucleo= a;
	
	l->next->nucleo = NULL;
	free(l->next);
	l->next = NULL;

exb(lista);
}



void arvore2(Node *center, int *base, int mais, int tam){
	int i; // para os for's
	 // cria o vetor um teco maior
	int vet[tam];
	if(tam != 0){
		vet[tam-1] = mais;
		if (tam!=1){
			for(i=1;i<tam;i++){
				vet[i-1] = base[i-1];
			}
		} 
	}
	if(center->right != NULL){ // caso tiver algo a direita aplique nele
		log_trace("rigt");
		arvore2( center->right, vet, 0, tam++);
	}
	if (center->left != NULL){ // caso estiver algo a esquerda aplique nele 
		log_trace("left");
		arvore2( center->left, vet, 1, tam++);
	}
	if ( (center->right == NULL) && (center->left == NULL) ) { // caso seja uma folha e nãto esteja apontando para mais ninguem. exiba!
		printf("[ %c por: ", (center->w)[0]);
		printf(" %d %d %d %d %d %d %d", vet[0], vet[1], vet[2], vet[3], vet [4], vet[5], vet[6]);
		//for(i=0;i<tam;i++) printf(" %d ",vet[i]); // exibir sequencia de 0's e 1's
		printf(" ]\n");
	} 
	
return;}


void arvore1(Node *center){
	if(center->right != NULL){ // caso tiver algo a direita aplique nele
		printf("0");
		arvore1( center->right);
	}
	if (center->left != NULL){ // caso estiver algo a esquerda aplique nele 
		printf("1");
		arvore1( center->left);
	}
	if ( (center->right == NULL) && (center->left == NULL) ) { // caso seja uma folha e nãto esteja apontando para mais ninguem. exiba!
		printf(" : %c\n", (center->w)[0]);
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
	Node *Nodd = (Node*) malloc(sizeof(Node));
	list *l = NULL;//(Node*) malloc(sizeof(Node));
	//(list*) malloc(sizeof(list));
	
	// do programa que copiei / editado
	int c;
	while(1) {
		c = fgetc(arq);
		if( feof(arq) )break;
		if (c>0){
			printf("[%d|%c]",c,c);
			//int w[1] = {c};
			add(&l, c);
		}
		
	}printf("\n");
	fclose(arq);
	
	
	log_trace("arv");
	
	printf("Folhas formadas:\n");
	exb(l);
	printf("\n\n");
	
	while(l->next != NULL){
		org(l);
		mesclar(l);
	}
	
	
	int *vet;
	arvore1(l->nucleo);
    arvore2(l->nucleo, vet, 0, 0);
	/*
	list *l = (list*) malloc(sizeof(list));
	printf("%p %p", l, l->nucleo);
	0x55e1b2d1d260 (nil)
	*/
}