#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

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
    HashStruct hashes;
    initHash(&hashes);
    printf("%d\n",hash("joao.preti@cba.ifmt.edu.br"));

    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    strcpy(c->nome,"Joao Paulo") ;
    strcpy(c->email,"joao.preti@cba.ifmt.edu.br");
    printf("%d\n",hash(c->email));
    put(&hashes, c->email, c, comparaChaves);
    printf("%d\n",hashes.hashes[hash("joao.preti@cba.ifmt.edu.br")].size);
    printf("%d\n",hashes.size);
    printf("%d\n",containsKey(&hashes, "joao.preti@cba.ifmt.edu.br", comparaChaves));
    
    Cliente *cliente = (Cliente*)get(&hashes, "joao.preti@cba.ifmt.edu.br", comparaChaves);
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