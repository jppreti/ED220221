#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct folha {
	int pai, elementosTotal, maxE, filhosTotal, maxF, pos;
	int* filhos;
	int* elementos;
};
typedef struct folha Folha;

struct arvore {
	int tam;
	Folha* folha;
};
typedef struct arvore Arvore;
void imprime(Arvore* arvore, Folha* f);


Folha* Iniciofolha(int tam) {
	Folha* folha = (Folha*)malloc(sizeof(Folha));

	folha->maxE = 2 * tam - 1;
	folha->pai = -1;
	folha->filhos = (int*)malloc(sizeof(int) * 2 * tam);
	folha->elementos = (int*)malloc(sizeof(int)*(2 * tam - 1));
	folha->elementosTotal = 0;
	folha->filhosTotal = 0;
	folha->pos = -1;
	folha->maxF = 2 * tam;

	for (int i = 0; i < folha->maxE; i++)
		folha->elementos[i] = -1;
	for (int i = 0; i < folha->maxF; i++)
		folha->filhos[i] = -1;

	return folha;
}
Arvore* inicio(int tam) {
	Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
	arvore->tam = tam;
	arvore->folha = NULL;
	FILE* arq;
	arq = fopen("words.txt", "r");

	return arvore;
}




int main( )
{
	
}