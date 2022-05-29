#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;
/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retornando: o endereço do nó criado
*/
No* novoNo(int x){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó novo!\n");
    return novo;
}

/*
    Retorna o valor maior dentre os dois valores
    a, b -> altura de dois nós da àrvore
    */
short maior(short a, short b){
    return (a > b)? a: b;
}

// Retorna a altura de um nó ou -1 caso ele seja nulo
short alturaDoNo(No *no)   {
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

// Calcular e retornar o fator de balanceamento de um nó
short fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}
//-------------------- ROTAÇÕES---------------------

// Função para rotação a esquerda
No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) +1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) +1;

    return y;
}

// Função para a rotação à direita
No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) +1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) +1;

    return y;
}

//  Rotação Esquerda Direita
No* rotacaoEsquerdaDireita(No *r){
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

// Rotação Direita Esquerda
No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}
/*
    Função para realizar o balanceamento da arvore após uma inserção ou remoção
    Recebe o Nó que esta desbalanceado e retorna a nova raiz após o balanceamento
*/
No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação á Esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);
    // Rotação a Direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);
    // Rotação dupla á Esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);
    // Rotação dupla á Direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}
/*
    Insere um novo Nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: Endereço do novo Nó ou a nova raiz após o balanceamento
    */
No* inserir(No *raiz, int x){
    if(raiz == NULL)//Árvore vazia
        return novoNo(x);
    else{//A inserção sera a esquerda ou a direita
        if(x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if(x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInserção não realizada!\nO elemento %d a existe!\n", x);
    }
    // Recalcular a altura de todos os Nós entre a raiz e o novo Nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verificar a necessidade de rebalancear a Árvore
    raiz = balancear(raiz);

    return raiz;
}
/*
    Função para remover um Nó da arvore binaria
    Pode ser necessario rebalancear a àrvore e a raiz pode ser alterada
    por isso prisamos retornar a raiz
*/
No* remover(No *raiz, int chave){
    if(raiz ==NULL){
        printf("\nValor não encontrado!\n");
        return NULL;
    }
    else{// Procurar o Nó a remover
       if(raiz->valor == chave) {
        // Romver Nós folhas (Nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL){
            free(raiz);
            printf("\nElemento folha removido!\n");
            return NULL;
            }
            else{// Remover Nós que possuem dois filhos
                    if(raiz->esquerdo != NULL && raiz->direito != NULL){
                        No *aux = raiz->esquerdo;
                        while(aux->direito != NULL)//Escrito dessa forma só para ficar mais compreencivél, (aux->direito)também funcionaria!
                            aux = aux->direito;
                        raiz->valor = aux->valor;
                        aux->valor = chave;
                        printf("\nElemento trocado: %d !\n", chave);
                        raiz->esquerdo = remover(raiz->esquerdo, chave);
                        return raiz;
                    }
                    else{// Remover Nós que possuem apenas um filho
                        No *aux;
                    if(raiz->esquerdo != NULL)
                        aux =raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("\nElemento com um filho removido: %d !\n", chave);
                    return aux;

                    }

            }

       }else{
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
       }
    // Recalcular todos os Nós entre a raiz eo novo Nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verificar a necessidade de rebalancear a Árvore
    raiz = balancear(raiz);

    return raiz;

    }
}
void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");
        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}
int main(){
    int opcao, valor;
    No *raiz = NULL;

   do{
     printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
     scanf("%d", &opcao);
     switch(opcao){
     case 0:
        printf("\tSaindo!!!");
        break;
     case 1:
        printf("\tDigite o valor a ser Inserido: ");
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
        break;
     case 2:
        printf("\tDigite o valor a ser removido: ");
        scanf("%d", &valor);
        raiz = remover(raiz, valor);
        break;
     case 3:
        imprimir(raiz, 1);
        break;
     default:
        printf("\nOpcão Invalida");
     }
    }while(opcao != 0);
return 0;
}
