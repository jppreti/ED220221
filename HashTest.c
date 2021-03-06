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
    log_trace("Entrando em comparaChaves");
    char *chave = (char*)key;
    log_debug("chave: %s", chave);
    Cliente *c = (Cliente*)data;
    log_debug("cliente c: %p", c);
    log_debug("c->nome: %s", c->nome);
    log_debug("c->email: %s", c->email);
    log_debug("%s == %s: %d", chave, c->email, strcmp (chave, c->email));
    log_trace("Saindo de comparaChaves");
    
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

    put(&hashes, c->email, c, comparaChaves);
    
    Cliente *cliente = (Cliente*)get(&hashes, "preti.joao@ifmt.edu.br", comparaChaves);
    
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