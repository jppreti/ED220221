//
//  
//  datastructure
//
//  Created by João Paulo Delgado Preti on 18/04/19.
//  Copyright © 2019 João Paulo Delgado Preti. All rights reserved.
//

#include "GeneralizedList.h"

int addAtom(Node **list, int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return -1;
    node->type=0;
    node->atomList.atom=data;
    node->tail=NULL;
    if (*list == NULL){
        *list = node;
    } else {
        Node *aux = NULL;
        for (aux = *list; aux->tail!=NULL; aux=aux->tail);
        aux->tail = node;
    }
    return 1;
}

int addList(Node **list, Node **subList) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return -1;
    node->type=1;
    node->atomList.list = *subList;
    node->tail=NULL;
    if (*list == NULL){
        *list = node;
    } else {
        Node *aux = NULL;
        for (aux = *list; aux->tail!=NULL; aux=aux->tail);
        aux->tail = node;
    }
    return 1;
}

Node* head(Node *list) {
    Node *headAux = NULL;
    if ((list)->type==0){
        headAux = (Node*)malloc(sizeof(Node));
        headAux->type=0;
        headAux->atomList.atom = (list)->atomList.atom;
        headAux->tail=NULL;
    }else{
        headAux = list->atomList.list;
    }
    return headAux;
}

Node* tail(Node *list) {
    return (list)->tail;
}

void showGeneralizedList(Node *list){
    printf("( ");
    Node *aux = NULL;
    for (aux = list; aux!=NULL; aux=aux->tail) {
        if (aux->type==0) {
            printf("%d ",aux->atomList.atom);
        } else {
            showGeneralizedList(aux->atomList.list);
        }
    }
    printf(")");
}

int depth(Node *list) {
    int profundidadeAtual = 0;
    if (list==NULL)
        return 0;
    
    Node *aux = NULL;
    for (aux = list; aux!=NULL; aux=aux->tail) {
        if (aux->type==1) {
            int prof = depth(aux->atomList.list);
            if (prof>profundidadeAtual)
                profundidadeAtual=prof;
        }
    }
    return profundidadeAtual+1;
}

int main() {
    Node *listaGeneralizada = NULL;
    printf("Lista: ");
    showGeneralizedList(listaGeneralizada);
    addAtom(&listaGeneralizada, 3);
    addAtom(&listaGeneralizada, 5);
    //printf("%d\n",listaGeneralizada->atomList.atomo);
    Node *lista2 = NULL;
    addAtom(&lista2, 7);
    addAtom(&lista2, 9);
    Node *lista3 = NULL;
    addAtom(&lista3, 11);
    addAtom(&lista3, 13);

    Node *lista4 = NULL;
    addAtom(&lista4, 15);
    addAtom(&lista4, 17);
    addList(&lista2, &lista4);
    
    Node *lista5 = NULL;
    addAtom(&lista5, 33);
    addAtom(&lista5, 44);
    addList(&lista3, &lista5);
    
    //    printf("%d\n",lista2->prox->atomList.atomo);
    addList(&listaGeneralizada, &lista2);
    addList(&listaGeneralizada, &lista3);

    //    printf("%d\n",listaGeneralizada->prox->prox->atomList.lista->atomList.atomo);
    
    printf("\nLista: ");
    showGeneralizedList(listaGeneralizada);
    printf("\nProfundidade: %d\n",depth(listaGeneralizada));
    
    printf("\nCauda: ");
    showGeneralizedList(tail(listaGeneralizada));
    
    printf("\n\nCabeca da Cauda: %d\n",head(tail(listaGeneralizada))->atomList.atom);
    printf("\n\nCabeca(Cauda(Cauda(Cabeca(Cauda(Cauda))))):\n");
    
    showGeneralizedList(head(tail(tail(head(tail(tail(listaGeneralizada)))))));
    
    printf("\n\nLista: ");
    showGeneralizedList(head(tail(tail(listaGeneralizada))));
    printf("\nProfundidade: %d\n",depth(head(tail(tail(listaGeneralizada)))));
    
    return 0;
}