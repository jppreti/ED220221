#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "log.h"

typedef struct Cliente {
    char nome[50];
    char email[50];
}Cliente;

bool comparaChaves(void *key, void *data) {
    char *chave = (char*)key;
    Cliente *c = (Cliente*)data;
    
    return (strcmp (chave, c->email) == 0)?true:false;
}

void printCliente(void *data) {
    Cliente *cliente = (Cliente*)data;
    printf("{%s,%s} - ", cliente->nome, cliente->email);
}

int main() {
    log_set_level(LOG_TRACE);
    HashStruct hashes;
    initHash(&hashes);
 
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Joao Paulo") ;
    strcpy(c->email,"preti.joao@ifmt.edu.br");
    //printf("Hash de preti.joao@ifmt.edu.br: %d\n",hash(c->email));
    put(&hashes, c->email, c, comparaChaves);
    printf("Size da lista: %d\n",hashes.hashes[hash("joao.preti@cba.ifmt.edu.br")].size);
    printf("Size do Hash: %d\n",hashes.size);
    //printf("preti.joao@ifmt.edu.br esta no hash? %d\n",containsKey(&hashes, "preti.joao@ifmt.edu.br", comparaChaves));
    
    Cliente *cliente = (Cliente*)get(&hashes, "preti.joao@ifmt.edu.br", comparaChaves);
    printf("%s\n",cliente->nome);
    
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Maria") ;
    strcpy(c->email,"maria@email.br");
    put(&hashes, c->email, c, comparaChaves);
    
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Pedro") ;
    strcpy(c->email,"pedro@email.com.br");
    put(&hashes, c->email, c, comparaChaves);
    
    c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Carla") ;
    strcpy(c->email,"carla@gmail.com.br");
    put(&hashes, c->email, c, comparaChaves);
       
    showHashStruct(&hashes, printCliente);
    return 0;
}