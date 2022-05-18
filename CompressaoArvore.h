typedef struct no{
	unsigned char caracter;
	int frequencia;
	struct no *esq, *dir, *proximo;
}No;

typedef struct lista{
	No *inicio;
	int tam;
}Lista;
	
char leitura(char filename);