#ifndef Blockchain_h
#define Blockchain_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha256.h"

enum boolean {
    true = 1 , false = 0
};

typedef enum boolean bool;

typedef struct Block{
    unsigned int index;
    char* previousHash;
    struct Block* previousBlock;
    unsigned long timestamp;
    float data;
    char* hash;
}Block;

typedef struct Blockchain{
    Block *genesisBlock;
    Block *latestBlock;
}Blockchain;

static void hashToString(char string[65], const uint8_t hash[32]){
    size_t i;
    for (i = 0; i < 32; i++){
        string += sprintf(string, "%02x", hash[i]);
    }
}

//char* calcHash(int, char *, unsigned long, float);
char *calcHash(int index, char *previusHash, unsigned long timestamp, float data){
    char input[1024];
    sprintf(input, "%i%s%lu%.8f", index, previusHash, timestamp, data);
    uint8_t hash[32];
    char *hash_string = (char*)malloc(sizeof(char)*65);
    calc_sha_256(hash, input, strlen(input));
    hashToString(hash_string, hash);

    return hash_string;
}

//void initBlockchain(Blockchain *);
void initBlockchain(Blockchain *blockchain){
Block *genesisBlock = (Block*)malloc(sizeof(Block));
genesisBlock->index = 0;
genesisBlock->previousHash = "0";
genesisBlock->previousBlock = NULL;
genesisBlock->timestamp = time(NULL);
genesisBlock->data = 100000;

genesisBlock->hash = calcHash(genesisBlock->index, genesisBlock->previousHash, genesisBlock->timestamp, genesisBlock->data);

blockchain->genesisBlock = genesisBlock;
blockchain->latestBlock = genesisBlock;
}

char *calcBlockHash(Block *block){
    return calcHash(block->index, block->previousHash, block->timestamp, block->data);
}

//Block* getLatestBlock(Blockchain *);
Block *getLatestBlock(Blockchain *blockchain){
    return blockchain->latestBlock;
}

//Block* genNextBlock(Blockchain *, float);
Block* genNextBlock(Blockchain *blockchain, float data){
    Block *previousBlock = getLatestBlock(blockchain);
    Block *newBlock = (Block*)malloc(sizeof(Block));

    newBlock->data = data;
    newBlock->previousHash = previousBlock->hash;
    newBlock->index = previousBlock->index+1;
    newBlock->timestamp = time(NULL);
    newBlock->hash = calcBlockHash(newBlock);

    return newBlock;
}



//bool isNewBlockValid(Block *, Block *);
bool isNewBlockValid(Block* newBlock, Block *previousBlock){
    if (previousBlock->index+1 != newBlock->index){
        return false;
    } else if (previousBlock->hash != newBlock->previousHash){
        return false;
    }else if (strcmp(calcBlockHash(newBlock), newBlock->hash) != 0){
      return false;  
    }
    return true;
}

//bool isBlockchainValid(Blockchain *);
bool isBlockchainValid(Blockchain *blockchain){
    Block *aux = getLatestBlock(blockchain);
    while (aux != blockchain->genesisBlock){
        if (!isNewBlockValid(aux, aux->previousBlock)){
            return false;
        }
        aux = aux->previousBlock;
    }
    return true;
}

//int addBlock(Blockchain *, Block *);
int addBlock(Blockchain *blockchain, Block *newBlock){
    if (isNewBlockValid(newBlock, getLatestBlock(blockchain))){
        newBlock->previousBlock = getLatestBlock(blockchain);
        blockchain->latestBlock = newBlock;
        return 1;
    }
    return -1;
}

#endif // !Bockchain._h
