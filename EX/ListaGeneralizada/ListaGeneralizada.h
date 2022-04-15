#ifndef LISTA_GENERALIZADA_H
#define LISTA_GENERALIZADA_H

#include <stdlib.h>
#include <stdio.h>

enum elem_t {type_int, type_sublist};

union list_info {
    int i;
    struct Node* sublist;
};

typedef struct Node{
    enum elem_t type;
    union list_info info;
    struct Node* next;
}Node;

Node* atom(int i){
    Node* n = (Node*)malloc(sizeof(Node));
    n->info.i = i;
    n->type = type_int;
    return n;
}

Node* subList(Node* sublist){
    Node* n = (Node*)malloc(sizeof(Node));
    n->info.sublist = sublist;
    n->type = type_sublist;
    return n;
}

Node *concat(Node* ap_elem, Node* ap_list){
    ap_elem->next = ap_list;
    return ap_elem;
}

Node* head(Node* l){

}

Node* tail(Node* l){

}

int depth(Node* l){
    int d = 0;
    while (l != NULL){
        if (l->type == type_int){
            d++;
        }
        else{
            d += depth(l->info.sublist);
        }
        l = l->next;
    }
    return d;
}

void show(Node* l){
    printf("(");
    while (l != NULL){
        switch (l->type){
            case type_int:
                printf("%d", l->info.i);
                break;
            case type_sublist:
                show(l->info.sublist);
                break;
        }
        l = l->next;
        if (l != NULL){
            printf(",");
        }
    }
    printf(")");
}

#endif
