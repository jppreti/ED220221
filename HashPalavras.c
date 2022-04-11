#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "log.h"
#define TAMANHO_IMG 320
#define TAMANHO_PX 10
#define LINHA 1024
#define COLUNA TAMANHO_PX

typedef struct Palavras {
    char palavra[100];
}Palavras;

bool comparaChaves(void *key, void *data) {
    char *chave = (char*)key;
    Palavras *c = (Palavras*)data;
    
    return (strcmp (chave, c->palavra) == 0)?true:false;
}

int matriz_ponteiro(int **mtr, size_t linhas, size_t colunas) {
     for (int lin = 0; lin < linhas; lin++) {
        for (int col = 0; col < colunas; col++) {
			printf("%d", mtr[lin][col]);
			//return mtr[lin][col];
		}
        //printf("\n");
    }
}

void main()
{
  log_set_level(LOG_INFO);
  HashStruct hashes;
  initHash(&hashes);
//  printf("tam: %d",hashes.size);
  FILE *arq;
  char Linha[100];
  char *result; 
  char texto[20];
  int divisor, i, j, k, z; 
	
  //clrscr();
  // Abre um arquivo TEXTO para LEITURA
  arq = fopen("ListaDePalavrasPT.txt", "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
     return;
  }
  i = 1;
  while (!feof(arq))
  {
	// Lê uma linha (inclusive com o '\n')
	  Palavras *c = (Palavras *)malloc(sizeof(Palavras));
      c = (Palavras *)malloc(sizeof(Palavras));
      result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      if (result)  // Se foi possível ler
	  strcpy(c->palavra,Linha);
	  put(&hashes, c->palavra, c, comparaChaves);
	  //printf("tam: %d %s",hashes.size,Linha);
      i++;
  }

	printf("\n tam: %d\n", hashes.size);

  	fclose(arq);
	
	int maior = 0;
  	for(i=0; i<LINHA; i++) {
  		printf("Qtde de elem do hash %d: %d\n",i,hashes.hashes[i].size);
			
  		if (hashes.hashes[i].size > maior) {
			maior = hashes.hashes[i].size;
		}	
	}
	//printf("maior = %d\n", maior);
	divisor = 255/maior;
	//printf("divisao do maior por 255 %d\n", 255/maior);
	
	arq = fopen("espalhamento.ppm", "w");
	
	sprintf(texto, "P3\n%d %d\n255\n", TAMANHO_IMG, TAMANHO_IMG); 
	fputs(texto, arq);
	
	char buffer[50];
	
	int **mtr = malloc(LINHA * sizeof(*mtr));
	
	for (int lin = 0, cont = 0; lin < LINHA; lin++) {
		mtr[lin] = malloc(COLUNA * sizeof(*mtr[lin]));
		for (int i = 0; i < hashes.size/(TAMANHO_IMG*TAMANHO_PX); i++) {		
			for (int col = 0; col < COLUNA; col++) {
				mtr[lin][col] = hashes.hashes[lin].size*divisor;
				sprintf(buffer, "%d %d %d\n", mtr[lin][col], 0, 0);
				fputs(buffer, arq);
			}
			fputs("0 0 0\n", arq);
		}
		//fputs("0 0 0\n", arq);
	}
	for (int i = 0; i < 10; i++) {
		matriz_ponteiro(mtr, LINHA, COLUNA);
	}
	printf("\n%d",hashes.size/(TAMANHO_IMG*TAMANHO_PX));
		//for(int i=0; i<LINHA; i++){
			//for(int k=0; k<10; k++){
				//for(int z=0; z<32; z++){
					//for(int j=0; j<10; j++){
						//char buffer[50];
						//sprintf(buffer, "%d %d %d\n", hashes.hashes[i].size*divisor, 0, 0);
						//sprintf(buffer, "%d %d %d\n", matriz_ponteiro(mtr, LINHA, COLUNA), 0, 0);
						//fputs(buffer, arq);
						//printf("\n%d\t%d", j, hashes.hashes[i].size*divisor);
					//}
					//printf(" - %d", i);
				//}	
			//}	
		//}
	
	fclose(arq);

}