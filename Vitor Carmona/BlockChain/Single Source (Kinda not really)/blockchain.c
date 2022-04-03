#include "blockchain.h"

int main(){
    Blockchain blockchain;
    printf("");
    initBlockchain(&blockchain);

    printf("%s\n", blockchain.genesisBlock->hash);
    printf("%lu\n", blockchain.genesisBlock->timestamp);

    Block *newBlock2 = genNextBlock(&blockchain, 80.0);
    addBlock(&blockchain, newBlock2);

    Block *newBlock3 = genNextBlock(&blockchain, 250.0);
    addBlock(&blockchain, newBlock3);
    
    printf("Block 2 validation : %i\n", isNewBlockValid(newBlock2, blockchain.genesisBlock));
    newBlock2->data = 74.00;
    printf("Blockchain validation : %i\n", isBlockchainValid(&blockchain));

    printf("size: %u\n", blockchain.latestBlock->index);

    return 0;
}