#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"


void initHash(HashStruct *hashStruct) {
    for (int i=0;i<MAX;i++) {
      
        init(&(hashStruct->hashes[i]));
    }
    hashStruct->size = 0;
}

int hash(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;
        return hash % MAX;
}


bool isHashEmpty(HashStruct *hashStruct) {
    return hashStruct->size==0;
}


int put(HashStruct *hashStruct, char *key, void *data, compare equal)  {
	if (!containsKey(hashStruct, key, equal)){
        
        int res = enqueue(&hashStruct->hashes[hash(key)],data);
      
        hashStruct->size+=res;
        return res;
    }
    return 0;
}

bool containsKey(HashStruct *hashStruct, char *key, compare equal) {

    int hashValue = hash(key);
    
    int pos = indexOf(&hashStruct->hashes[hashValue], key, equal);
  
    return (pos!=-1)?true:false;
}
void* get(HashStruct *hashStruct, char *key, compare equal) {
    
    int hashValue = hash(key);
    
    Node *aux = hashStruct->hashes[hashValue].first->next;
   
    while(aux!=hashStruct->hashes[hashValue].first && !equal(aux->data, key))
        aux=aux->next;
    return aux->data;
}

void* removeKey(HashStruct *hashStruct, char *key, compare equal) {
    int hashValue = hash(key);
    int pos = indexOf(&hashStruct->hashes[hashValue], key, equal);
	
    void* result = removePos(&hashStruct->hashes[hashValue], pos);
	
    if (result!=NULL) hashStruct->size--;
    return result;
}


void showHashStruct(HashStruct *hashStruct, printNode print) {

    for (int i=0; i < MAX; i++) {
        printf("Hash %d tem %d elementos: ",i,hashStruct->hashes[i].size);
        show(&hashStruct->hashes[i],print);
        printf("\n");
    }
   
    printf("\n\nForam inseridas %d palavras nesta tabela.\n\n",hashStruct->size);
}

bool comparaChaves(void *key, void *data) {
    char *chave = (char*)key;
    Palavra *c = (Palavra*)data;
    return (strcmp (chave, c->texto) == 0)?true:false;
}

void printPalavra(void *data) {
    Palavra *palavra = (Palavra*)data;
    printf("{%s} - ", palavra->texto);
}

void imprimeColisoes(HashStruct *hashStruct, printNode print) {
    int cont=0;
    
    
    printf("\n\t");
    for (int i=0; i < MAX; i++) 
        if ((hashStruct->hashes[i].size)>1){
            printf("%d\t",i);
            cont++;
        }
  
    printf("\n\n\nForam contabilizados %d elementos nesta tabela, tendo ocorrido",hashStruct->size);
    
    printf(" %d colisoes.",cont);
}

void porcentagemHash(HashStruct *hashStruct){
        float contador = 0.0;
        for (int i=0; i < MAX; i++) {
            if(hashStruct->hashes[i].size >= 1){
                contador += 1;
            }
        }
    printf("\n A PORCENTAGEM DE OCUPACAO FOI DE %.2f%%", (contador/MAX)*100 );
}

void mapaEspalhamento(HashStruct *hashStruct){
    int var;
    int dim_tab=raiz_Qd();
    FILE *imageFile;
    //int larg=55,alt=55;
    int larg=dim_tab;
    int alt=dim_tab;
    imageFile=fopen("imagem.ppm","wb");
    if(imageFile==NULL){
        perror("ERROR: Cannot open output file");
        exit(EXIT_FAILURE);
    }
   
    fprintf(imageFile,"P3\n");               
    fprintf(imageFile,"%d %d\n",larg,alt);   
    fprintf(imageFile,"255\n");             
    for (int i=0; i < MAX; i++) {
        
        if ((hashStruct->hashes[i].size)!= 0){  
            if ((hashStruct->hashes[i].size) >= 1){
                var=255/(hashStruct->hashes[i].size);
                fprintf(imageFile,"0 %d 0\n",var);
            }
        }else
            fprintf(imageFile,"241 255 162\n");
    }
    printf("\n\nArquivo PPM gerado com sucesso. Visualize o arquivo na pasta de execucao deste programa.");
    fclose(imageFile);
}

void carregaArquivo(HashStruct *hashStruct,Palavra *t_palavra){
    Palavra *c = (Palavra *)malloc(sizeof(Palavra));
    char url[]="lista.txt";
    FILE *arq;
    arq = fopen(url, "r");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while(!feof(arq)){ 
            c = (Palavra *)malloc(sizeof(Palavra));
            fscanf(arq, "%s", c->texto);
            put(hashStruct, c->texto, c, comparaChaves);
        }
        printf("\nArquivo carregado com sucesso!");
        fclose(arq);
}
int raiz_Qd(){
    int n;
    float recorre = MAX;
   
    for (n = 0; n < 10; ++n)
          recorre = recorre/2 + MAX/(2*recorre);
           
    return(recorre);    
}    

