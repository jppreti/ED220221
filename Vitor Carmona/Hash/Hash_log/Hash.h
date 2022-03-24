#ifndef DataStructure_Hash_h
#define DataStructure_Hash_h

#include "HashDLL.h"

#define MAX 10

typedef struct HashStruct{
        DoublyLinkedList hashes[MAX];
        int size;
}hashSt;

void initHash(hashSt *);
bool isHashEmpty(hashSt *);
int hashVal(char *);
int put(hashSt *, char *, void *, compare);
bool containKey(hashSt *, char *, compare);
void* get(hashSt *, char *, compare);
void* removeKey(hashSt *, char *, compare);
void showStructHash(hashSt *, printNode);

#endif

