#include "Blockchain.h"
#include <string.h>
#include "sha-256.h"
#include <time.h>
#include "log.h"

void initBlockchain(Blockchain *blockchain) {
    log_trace("Entrando em initBlockchainn");
    log_info("Criando o bloco gênesis");
    Block *genesisBlock = (Block*)malloc(sizeof(Block));
    genesisBlock->index = 0;
    genesisBlock->previousHash = "0";
    genesisBlock->previousBlock = NULL;
    genesisBlock->timestamp = time(NULL);
    genesisBlock->data = 1000000;
    
    genesisBlock->hash = calculateHash(genesisBlock->index, genesisBlock->previousHash, genesisBlock->timestamp, genesisBlock->data);

    log_debug("genesisBlock: %p", genesisBlock);
    log_debug("genesisBlock->data: %d", genesisBlock->data);
    log_debug("genesisBlock->hash: %s", genesisBlock->hash);

    blockchain->genesisBlock = genesisBlock;
    blockchain->latestBlock = genesisBlock;
    log_trace("Saindo de initBlockchain");
}

static void hash_to_string(char string[65], const uint8_t hash[32]) {
    log_trace("Entrando em hash_to_string");
    size_t i;
    for (i = 0; i < 32; i++) {
        //montar uma string com 64 caracteres hexadecimais
        string += sprintf(string, "%02x", hash[i]); //02x hexadecimal em 2 caracteres
    }
    log_trace("Saindo de hash_to_string");
}

char* calculateHash(int index, char* previousHash, unsigned long timestamp, float data) {
    log_trace("Entrando em calculateHash");
    char input[1024];
    sprintf(input, "%i%s%lu%.8f",index,previousHash, timestamp, data);
    //vetor de 32 bytes de inteiros unsigned [0-255] (256/8 = 32)
    uint8_t hash[32];
    //char hash_string[65];
    char *hash_string = (char*)malloc(sizeof(char)*65);
    calc_sha_256(hash, input, strlen(input));
    hash_to_string(hash_string, hash);
    log_debug("hashString: %s", hash_string);
    log_trace("Saindo de CalculateHash");
    return hash_string;
}

char* calculateBlockHash(Block *block) {
    return calculateHash(block->index, block->previousHash, block->timestamp, block->data);
}

Block* generateNextBlock(Blockchain *blockchain, float data) {
    log_trace("Entrando em generateNextBlock");
    log_info("Criando novo Bloco");
    Block *previousBlock = getLatestBlock(blockchain);
    Block *newBlock = (Block*)malloc(sizeof(Block));
    
    newBlock->data = data;
    newBlock->previousHash = previousBlock->hash;
    newBlock->index = previousBlock->index+1;
    newBlock->timestamp = time(NULL);
    newBlock->hash = calculateBlockHash(newBlock);
    log_debug("newBlock: %p", newBlock);
    log_debug("newBlock->data: %.6f", newBlock->data);
    log_debug("newBlock->time: %lu", newBlock->timestamp);
    log_debug("newBlock->hash: %s", newBlock->hash);
    log_trace("Saindo de generateNextBlock");
    return newBlock;
}

Block* getLatestBlock(Blockchain *blockchain) {
    log_trace("Entrando em getLatestBlock");
    log_debug("latestBlock: %p", blockchain->latestBlock);
    log_trace("Saindo de getLatestBlock");
    return blockchain->latestBlock;
}

bool isValidNewBlock(Block* newBlock, Block* previousBlock) {
    log_trace("Entrando em isValidNewBlock");
    log_debug("previousBlock->index: %d", previousBlock->index);
    log_debug("newBlock->index: %d", newBlock->index);
    log_debug("previousBlock->hash: %d", previousBlock->hash);
    log_debug("newBlock->previousHash: %d", newBlock->previousHash);
    log_trace("Saindo de isValidNewBlock");
    if (previousBlock->index + 1 != newBlock->index) {
        return false;
    } else if (previousBlock->hash != newBlock->previousHash) {
        return false;
    } else if (strcmp(calculateBlockHash(newBlock),newBlock->hash)!=0) {
        return false;
    }
    return true;
}

bool isBlockchainValid(Blockchain *blockchain) {
    log_trace("Entrando em isBlockchainValid");
    Block *aux = getLatestBlock(blockchain);
    while (aux!=blockchain->genesisBlock) {
        if (!isValidNewBlock(aux, aux->previousBlock))
            return false;
        aux = aux->previousBlock;
    }
    log_trace("Saindo de isBlockchainValid");
    return true;
}

int addBlock(Blockchain *blockchain, Block *newBlock) {
    log_trace("Entrando em addBlock");
    if (isValidNewBlock(newBlock, getLatestBlock(blockchain))) {
        newBlock->previousBlock = getLatestBlock(blockchain);
        blockchain->latestBlock = newBlock;
        return 1;
    }
    log_trace("Saindo de addBlock");
    return -1;
}