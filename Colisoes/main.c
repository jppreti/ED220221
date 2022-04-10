#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Hash.h"
#include "log.h"

typedef struct Palavras {
    char p[999];
}Palavras;

bool comparaChaves(void *key, void *data) {
    log_trace("Entrando em comparaChaves");
    char *chave = (char*)key;
    log_debug("chave: %s", chave);
    Palavras *c = (Palavras*)data;
    log_debug("cliente c: %p", c);
    log_trace("Saindo de comparaChaves");
    
    return (strcmp (chave, c->p) == 0)?true:false;
}

void printCliente(void *data) {
    Palavras *cliente = (Palavras*)data;
    printf("  %s", cliente->p);
}

int main()
{
    FILE *arq;
    char *result;
    char linha[999];
    int i;
    
/* Abrindo e gravando o arquivo txt */
    
    if (arq == NULL) 
    {
        arq=fopen("Arqpalavras.txt","rt");
    }
    else 
    printf("Não foi possível abrir arquivo\n");
    
	/*char palavras = fgetc(arq);
    while (palavras != EOF)
    {
        printf ("%c", palavras);
        palavrass = fgetc(arq);
    }
    printf("%s",arq);)*/


/* distribuindo a lista de palavras na tabela Hash*/
    
	log_set_level(LOG_WARN);
    HashStruct hashes;
    initHash(&hashes);
    
    
 
   while (!feof(arq))
  
      {
    	//printf("%s", &linha);
        Palavras *c = (Palavras *)malloc(sizeof(Palavras));
        result= fgets(linha, 999, arq);
        if(result)
        
        {
            printf("%d: %s", i, linha);
    	    strcpy(c->p, linha);
    	    printf("%s", linha);
    	    put(&hashes, c->p, c, comparaChaves);
        }
    	i++;
	}
    fclose(arq);
   showHashStruct(&hashes, printCliente);
    
/* Tamanho das colisões */

   /* FILE *pixel;
    pixel = fopen("grafico.ppm", "wt");
	if (pixel == NULL)
	{
	    printf("Problemas na CRIACAO do arquivo\n");
        printf("%s", pixel);
	}
	*/
	
    int maior = 0, cont;
    float escala;
    
    for (cont = 0; cont<MAX; cont++ )
    {
        if (maior < hashes.hashes[cont].size){
            maior = hashes.hashes[cont].size;
        }
    }
    escala = 255/maior;
   
    
    int intensidade[MAX];
    for (cont = 0; cont<MAX; cont++ ){
        
        intensidade[cont] = escala * hashes.hashes[cont].size;

    }
    showHashStruct(&hashes, printCliente);
    for (cont = 0; cont<MAX; cont++ )
    {
        printf("%d ",intensidade[cont]);

    }
    
    //Criando o arquivo 
    
    //printf("\n%f -- %d",escala, maior);
    arq = NULL;
    arq = fopen("Pixel.ppm", "w");
    if (arq == NULL)
    {
        printf("Problemas na CRIACAO do arquivo\n");
        
    }
    int cont1, cont2, cont3, cont4;
    fputs("\nP3\n32 32\n255\n", arq);
    for (cont1 = 0; cont1<MAX; cont1++ )
    {
         for(cont4 = 0; cont4<10;cont4++)
         {
            for(cont2 = 0;cont2<32;cont2++)
            {
                for(cont3 = 0;cont3<10;cont3++)
                {
                   fprintf(arq,"%d 0 %d \n", intensidade[cont1+cont2], intensidade[cont1+cont2]);
                }
            }
        }
        
    }

    fclose(arq);
    return 0;
}






