#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#ifndef GENERALIZEDLINKEDLIST_H_INCLUDED
#define GENERALIZEDLINKEDLIST_H_INCLUDED

/*enum boolean {
    true = 1, false = 0
};
typedef enum boolean bool;*/

typedef struct No {
    int t;
    union {
        int atom;
        struct No *list;
    }atomList;
    struct No *next;
}No;

int addAtom(No **list, int put);
int addList(No **list, No **subList);
// funcao para adicionar uma navegacao entre as listas.
// funcao para adicionar um item em uma posicao da lista.
No* head(No *list);
No* tail(No *list);
void show(No *list);
bool search(No *list, int atom);
int depth(No *list);
void showMe( No *list);
void ln();

#endif // GENERALIZEDLINKEDLIST_H_INCLUDED
