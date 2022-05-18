#define ASCII 256
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "CompressaoArvore.h"
#define TAM 256

void inicializa_tab_com_zero(unsigned int tab[]){
	int i;
	for(i = 0; i < TAM; i++){
		tab[i]=0;
	}
}

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]){
	int i = 0;
	while(texto[i] != '\0'){
		tab[texto[i]]++;
		i++;
	}
}

void imprime_tab_frequencia(unsigned int tab[]){
	int i;
	printf("\tTabela de Frequência\n");
	for (i=0; i<TAM; i++){
		if(tab[i]>0)
			printf("\t%d = %u = %c\n", i, tab[i], i);
	}
}

void criar_lista(Lista *lista){
	lista->inicio = NULL;
	lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
	log_trace("Entrando em inserir_ordenado");
	No *aux;
	if (lista->inicio == NULL){
		lista->inicio = no;
	}else if (no->frequencia < lista->inicio->frequencia){
		no->proximo = lista->inicio;
		lista->inicio = no;
	}else{
		aux = lista->inicio;
		while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
			aux = aux->proximo;
		no->proximo = aux->proximo;
		aux->proximo = no;
	}
	log_trace("Saindo de inserir_ordenado");
	lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
	int i;
	No *novo;
	for(i = 0; i < TAM; i++){
		if(tab[i] > 0){
			novo = malloc(sizeof(No));
			if(novo){
				novo->caracter = i;
				novo->frequencia = tab[i];
				novo->dir = NULL;
				novo->esq = NULL;
				novo->proximo = NULL;
				
				inserir_ordenado(lista, novo);
				
			}else{
				printf("\tErro ao alocar memória em preencher_lista\n");
				break;
			}
		}
	}
}

void imprimir_lista(Lista *lista){
	No *aux = lista->inicio;
	printf("\n\tLista ordenada: tamanho: %d\n", lista->tam);
	while(aux){
		printf("\tCaracter %c Frequência:%d\n", aux->caracter, aux->frequencia);
		aux = aux->proximo;
	}
}

No* remove_no_inicio(Lista *lista){
	log_trace("Entrando em remove_no_inicio");
	No *aux = NULL;
	if(lista->inicio){
		aux = lista->inicio;
		lista->inicio = aux->proximo;
		aux->proximo = NULL;
		lista->tam--;
	}log_debug("No removido %p, Lista tamanho %d", aux, lista->tam);
	log_trace("Saindo de remove_no_inicio");
	return aux;
}

No* montar_arvore(Lista *lista){
	log_trace("Entrando em montar_arvore");
	No *primeiro, *segundo, *novo;
	while(lista->tam > 1){
		primeiro = remove_no_inicio(lista);
		segundo = remove_no_inicio(lista);
		novo = malloc(sizeof(No));
		
		log_debug("Novo %p", novo);
		if(novo){
			log_debug("If Novo %p", novo);
			novo->caracter = '+';
			log_debug("Caracter %c", novo->caracter);
			novo->frequencia = primeiro->frequencia + segundo->frequencia;
			log_debug("Frequencia %d", novo->frequencia);
			novo->esq = primeiro;
			log_debug("Esquerda %p", novo->esq);
			novo->dir = segundo;
			log_debug("Direia %p", novo->dir);
			novo->proximo = NULL;
			log_debug("Proximo %p", novo->proximo);
			log_debug("Caracter: %c, Frequencia: %d, Esquerda: %p, Direita %p", novo->caracter, novo->frequencia, novo->esq, novo->dir);
			
			inserir_ordenado(lista, novo);
			log_trace("Saindo de inserir_ordenado");
		}else{
			printf("\n\tErro ao alocar memoria em montar _arvore!\n");
			break;
		}
	}
	log_trace("Saindo de montar_arvore");
	return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam){
	if(raiz->esq == NULL && raiz->dir == NULL){
		printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
	}else{
		imprimir_arvore(raiz->esq, tam + 1);
		imprimir_arvore(raiz->dir, tam + 1);
	}
}

int altura_arvore(No *raiz){
	int esq, dir;
	if(raiz == NULL)
		return -1;
	else{
		esq = altura_arvore(raiz->esq) + 1;
		dir = altura_arvore(raiz->dir) + 1;
		
		if(esq > dir)
			return esq;
		else
			return dir;
	}
}

char** aloca_dicionario(int colunas){
	char **dicionario;
	int i;
	dicionario = malloc(sizeof(char*) * TAM);
	for(i = 0; i < TAM; i++)
		dicionario[i] = calloc(colunas, sizeof(char));
	return dicionario;
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){
	//log_trace("Dentro de gerar_dicionario");
	char esquerda[colunas], direita[colunas];
	if(raiz->esq == NULL && raiz->dir == NULL){
		strcpy(dicionario[raiz->caracter], caminho);
		//log_trace("If raiz");
	}else{
		//log_trace("Else raiz");
		strcpy(esquerda, caminho);
		strcpy(direita, caminho);
		strcat(esquerda, "0");
		strcat(direita, "1");
		gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
		gerar_dicionario(dicionario, raiz->dir, direita, colunas);
	}
}

void imprime_dicionario(char **dicionario){
	int i;
	printf("\n\tDicionario:\n");
	for(i = 0; i < TAM; i++){
		if(strlen(dicionario[i]) > 0)
			printf("\t%3d: %s\n", i, dicionario[i]);
	}
}

int calcula_tamanho_string(char **dicionario, unsigned char *texto){
	int i = 0, tam = 0;
	while(texto[i] != '\0'){
		tam = tam + strlen(dicionario[texto[i]]);
		i++;
	}
	return tam + 1;
}

char* codificar(char **dicionario, unsigned char *texto){
	int i = 0, tam = calcula_tamanho_string(dicionario, texto);
	char *codigo = calloc(tam, sizeof(char));
	while(texto[i] != '\0'){
		strcat(codigo, dicionario[texto[i]]);
		i++;
	}
	return codigo;
}

char* decodificar(unsigned char texto[], No *raiz){
	int i = 0;
	No *aux = raiz;
	char temp[2];
	char *decodificado = calloc(strlen(texto), sizeof(char));
	while(texto[i] != '\0'){
		if(texto[i] == '0')
			aux = aux->esq;
		else
			aux = aux->dir;
		if(aux->esq == NULL && aux->dir == NULL){
			temp[0] = aux->caracter;
			temp[1] = '\0';
			strcat(decodificado, temp);
			aux = raiz;
		}
		i++;
	}
	return decodificado;
}

void compactar(unsigned char str[]){
	FILE *arquivo = fopen("compactado.ef", "wb");
	int i = 0, j = 7;
	unsigned char mascara, byte = 0;
	if(arquivo){
		while(str[i] != '\0'){
			mascara = 1;
			if(str[i] == '1'){
				mascara = mascara << j;
				byte = byte | mascara;
			}
			j--;
			if(j < 0){
				fwrite(&byte, sizeof(unsigned char), 1, arquivo);
				byte = 0;
				j = 7;
			}
			i++;
		}
		if(j != 7)
			fwrite(&byte, sizeof(unsigned char), 1, arquivo);
		fclose(arquivo);
	}
	else
		printf("\nErro ao abrir/criar o arquivo em compactar\n");
}

unsigned int eh_bit_um(unsigned char byte, int i){
	unsigned char mascara = (1 << i);
	return byte & mascara;
}

void descompactar(No *raiz){
	FILE *arquivo = fopen("compactado.ef", "rb");
	No *aux = raiz;
	unsigned char byte;
	int i;
	if(arquivo){
		while(fread(&byte, sizeof(unsigned char), 1, arquivo)){
			for(i = 7; i <= 0; i++){
				if(eh_bit_um(byte, i))
					aux= aux->dir;
				else
					aux = aux->esq;
				if(aux->esq == NULL && aux->dir == NULL){
					printf("%c", aux->caracter);
					aux = raiz;
				}
			}
		}
		fclose(arquivo);
	}
	else
		printf("\nErro ao abrir o arquivo em descompactar\n");
}

int main() {
	log_set_level(LOG_INFO);
	unsigned char texto[] = "Vamos aprender programação!";
    unsigned int tabela_frequencia[TAM];
 	Lista lista;
	No *arvore;
	int colunas;
	char **dicionario;
	char *codificado, *decodificado;
	
	setlocale(LC_ALL,"");
	
	inicializa_tab_com_zero(tabela_frequencia);
	preenche_tab_frequencia(texto, tabela_frequencia);
	imprime_tab_frequencia(tabela_frequencia);
    
 	criar_lista(&lista);
	preencher_lista(tabela_frequencia, &lista);
	imprimir_lista(&lista);
	
	arvore = montar_arvore(&lista);
	printf("\n\tÁrvore de Huffmam\n");
	imprimir_arvore(arvore, 0);
	
	colunas = altura_arvore(arvore) + 1;
	
	dicionario = aloca_dicionario(colunas);
	log_trace("Entrando em gerar_dicionario");
	gerar_dicionario(dicionario, arvore, "", colunas);
	log_trace("Entrando em imprime_dicionario");
	imprime_dicionario(dicionario);
	
	codificado = codificar(dicionario, texto);
	printf("\n\tTexto codificado: %s\n", codificado);
	
	decodificado = decodificar(codificado, arvore);
	printf("\n\tTexto decodificado: %s\n", decodificado);
	
    return 0;
}