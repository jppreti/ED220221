#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 256
//No será utilizado tanto para a lista e para a arvore
typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;//esq e dir é para a arv e pro é para a lista
}No;

//para evitar ter que passar **p utilizamos struct lista
typedef struct{
    No *inicio;
    int tam;
}Lista;

//-----------  tabela de frequência ----------------------

//zera a tabela 
void inicializa_tabela(unsigned int tab[]){
    int i;
    for(i = 0; i < TAM; i++)
        tab[i] = 0;
}

//calcula frequencia
void tab_frequencia(unsigned char texto[], unsigned int tab[]){
    int i = 0;

    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}
//imprimi frequencia
void imprime_tab(unsigned int tab[]){
    int i;

    printf("\tTABELA DE FREQUENCIA\n");
    printf("\tASC II \t FREQUENCIA \t CARACTER\n");
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0)
            printf("\t%d  \t\t%u  \t\t%c\n", i, tab[i], i);
    }
}

//----------- Gerar Lista  ----------------------

void Lista_encadeada(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;
    // se a lista estiver vazia insere um No
    if(lista->inicio == NULL){
        lista->inicio = no;
        
    }
    // verifica se a fequencia do novo No é menor do que as existentes
    else if(no->frequencia < lista->inicio->frequencia){
        no->proximo = lista->inicio;
        lista->inicio = no;
       
    }
    //para inserir um No no meio da lista ou no fim
    else{
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
        
    }
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
            }
            else{
                printf("\tErro ao alocar memoria \n");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\n\tLista \n");
    while(aux){
                printf("\tCaracter: %c Frequência: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

//-------------  Montar a Árvore de Huffman ----------------------

No* remove_no_inicio(Lista *lista){
    No *aux = NULL;

    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;
}

No* montar_arvore(Lista *lista){
    No *primeiro, *segundo, *novo;
    while(lista->tam > 1){
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if(novo){
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }
        else{
            printf("\n\tErro ao alocar memoria \n");
            break;
        }
    }
    return lista->inicio;
}


void imprimir_arvore(No *raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\t %c\t\t %d\n", raiz->caracter, tam);
        
    else{
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}
//--------------------- Compressão de dados ---------------------------------
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
    char esquerda[colunas], direita[colunas];

    if(raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->caracter], caminho);
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprime_dicionario(char **dicionario,unsigned int tab[]){
    int i,cont;
    printf("\n\tDicionario\n");
    printf("\n\tChar \tFreq. Bits\tTotal bits \tBinário \n");

    for(i = 0; i < TAM; i++){
        if(strlen(dicionario[i]) > 0)
        printf("\t%c \t%d \t%ld \t%ld \t\t%s\n", i,tab[i],strlen(dicionario[i]), strlen(dicionario[i])*tab[i],dicionario[i]);
    }
    
    cont=0;
    for(i = 0; i < TAM; i++)
    {
        if(strlen(dicionario[i]) > 0)
        cont=cont+ strlen(dicionario[i])*tab[i];
    }
     printf("\nTotal da compressão %d \t%d",cont, TAM);
}

int main(){

    unsigned char texto[] = "A codificação de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo";
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas;
    char **dicionario;
    char *codificado, *decodificado;

    setlocale(LC_ALL, "Portuguese");

    //-----------  tabela de frequencia ---------------
    inicializa_tabela(tabela_frequencia);
    tab_frequencia(texto, tabela_frequencia);
    imprime_tab(tabela_frequencia);

    //----------- Lista Encadeada Ordenada -----------
    Lista_encadeada(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);

    //----------- Montar a Árvore de Huffman ---------
    arvore = montar_arvore(&lista);
    printf("\n\tÁrvore de Huffam\n\n");
    printf("\tFolha \t\tAltura\n\n");
    imprimir_arvore(arvore, 0);
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprime_dicionario(dicionario,tabela_frequencia);
  
    return 0;
}








