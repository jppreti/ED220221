#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "log.h"

void initHash(hashSt *hash){
    log_trace("");
    for(int i = 0; i < MAX; i++){
        init(&(hash->hashes[i]));
    }
    hash->size=0;
}

bool isHashEmpty(hashSt *hash){
    return hash->size=0;
}

int hashVal(char *key){
    int sum=0;
    for (int i = 0; key[i] != 0; i++)
    {
        sum += key[i] * (i+1);
    }
    return sum%MAX;
}

int put(hashSt *hash, char *key, void *data, compare equal){
    if (!containKey(hash, key, equal)){
        int res = enqueue(&hash->hashes[hashVal(key)], data);
        hash->size+=res;
        return res;
    }
    return 0;
}

bool containKey(hashSt *hash, char *key, compare equal){
    int hashValue = hashVal(key);
    int pos = indexOf(&hash->hashes[hashValue], key, equal);

    return(pos != -1)?true:false;
}

void* get(hashSt *hash, char *key, compare equal){
    int hashValue = hashVal(key);
    Node *aux = hash->hashes[hashValue].first->next;
    while(aux != hash->hashes[hashValue].first && !equal(aux->data, key))
        aux=aux->next;

    return aux->data;
}

void* removeKey(hashSt *hash, char *key, compare equal){
    int hashValue = hashVal(key);
    int pos = indexOf(&hash->hashes[hashValue], key, equal);
    void* result = removePos(&hash->hashes[hashValue], pos);
    if(result != NULL) 
        hash->size--;
    return result;
}

void showStructHash(hashSt *hash, printNode print){
    printf("There are %d elements in the Hash\n\n", hash->size);
    for(int i = 0; i < MAX; i++){
        printf("Hash %d has %d elements: ", i, hash->hashes[i].size);
        show(&hash->hashes[i],print);
        printf("\n");
    }
}

typedef struct Client{
    char nome[50];
    char email[50];
}Client;

bool compareKeys(void *key, void *data){
    char *k = (char*)key;
    Client *c = (Client*)data;

    return(strcmp(k, c->email) == 0)?true:false;
}

void printClient(void *data){
    Client *cli = (Client*)data;
    printf("{%s , %s} - ", cli->nome, cli->email);
}

int main(){
    hashSt hash;
    initHash(&hash);
    printf("%d\n", hashVal("joao.preti@cba.ifmt.edu.br"));

    Client *c = (Client *)malloc(sizeof(Client));

    strcpy(c->nome, "Joao Paulo");
    strcpy(c->email,"joao.preti@cba.ifmt.edu.br");
    printf("%d\n",hashVal(c->email));
    put(&hash, c->email, c, compareKeys);
    printf("%d\n", hash.hashes[hashVal("joao.preti@cba.ifmt.edu.br")].size);
    printf("%d\n", hash.size);
    printf("%d\n", containKey(&hash, "joao.preti@cba.ifmt.edu.br", compareKeys));

    Client *cli = (Client*)get(&hash, "joao.preti@cba.ifmt.edu.br", compareKeys);
    printf("%s\n", cli->nome);

    c = (Client *)malloc(sizeof(Client));
    strcpy(c->nome,"Maria");
    strcpy(c->email,"maria@gmail.com");
    put(&hash, c->email, c, compareKeys);

    c = (Client *)malloc(sizeof(Client));
    strcpy(c->nome,"Pedro");
    strcpy(c->email,"pedro@gmail.com");
    put(&hash, c->email, c, compareKeys);

    c = (Client *)malloc(sizeof(Client));
    strcpy(c->nome,"Carla");
    strcpy(c->email,"carla@gmail.com");
    put(&hash, c->email, c, compareKeys);

    showStructHash(&hash, printClient);
    return 0;
}
