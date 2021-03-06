#include "Blockchain.h"
#include "log.h"

int main() {
    log_set_level(LOG_INFO);
    Blockchain blockchain;

    initBlockchain(&blockchain);

    printf("%s\n",blockchain.genesisBlock->hash);
    printf("%lu\n",blockchain.genesisBlock->timestamp);
    
    Block *newBlock2 = generateNextBlock(&blockchain,80.0);
    addBlock(&blockchain, newBlock2);
    
    Block *newBlock3 = generateNextBlock(&blockchain,250.0);
    addBlock(&blockchain, newBlock3);
    
    printf("Block 2 is valid? %i\n",isValidNewBlock(newBlock2, blockchain.genesisBlock));
    newBlock2->data = 74.00;
    printf("Blockchain is valid? %i\n",isBlockchainValid(&blockchain));

    printf("size: %u\n",blockchain.latestBlock->index);
	
	Block *aux = getLatestBlock(&blockchain);
    while (aux!=blockchain.genesisBlock) {
		printf("hash: %s\n",aux->hash);	
		printf("phash: %s\n",aux->previousHash);
        aux = aux->previousBlock;
	}
	
    return 0;
}