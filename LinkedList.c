#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void init(LinkedList *list) {
    list->first=NULL;
    list->size=0;
}

int enqueue(LinkedList *list, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(list))            //se a lista estiver vazia
        list->first = newNode;    //novo nó é o primeiro
    else {
        Node *aux = list->first;  //aux aponta para o primeiro
        while (aux->next != NULL) //enquanto não for o último nó
            aux = aux->next;      //aux avança para o nó seguinte
        aux->next = newNode;      //último nó aponta para o novo nó
    }

    list->size++;
    return 1;
}

void* dequeue(LinkedList *list) {
    if (isEmpty(list)) return NULL;

    Node *trash = list->first;
    list->first = list->first->next;
    
    void *data = trash->data;
    free(trash);
    list->size--;
    
    return data;
}

void* first(LinkedList *list) {
    return (isEmpty(list))?NULL:list->first->data;
}

void* last(LinkedList *list) {
    void *data = NULL;
    if (!isEmpty(list)) {          //Se a lista não estiver vazia
        Node *aux = list->first;   //aux aponta para o primeiro nó
        while (aux->next != NULL)  //enquanto não for o último nó
            aux = aux->next;       //aux avança para o nó seguinte
        data = aux->data;          //endereço de memória do dado no último nó
    }
    return data;
}

int push(LinkedList *list, void *data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    newNode->data = data;
    newNode->next = NULL;
    
    if (isEmpty(list))               //se a lista estiver vazia
        list->first = newNode;       //novo nó é o primeiro
    else {
        newNode->next = list->first; //o topo atual será o segundo da lista
        list->first = newNode;       //o novo nó será o topo
    }

    list->size++;
    return 1;
}

void* pop(LinkedList *list) {
    return dequeue(list);
}

void* top(LinkedList *list) {
    return first(list);
}

bool isEmpty(LinkedList *list) {
    return (list->size==0);
}

int indexOf(LinkedList *list, void *data, compare equal) {
    if (isEmpty(list)) return -1;
    int count=0;
    Node *aux = list->first;
   
    while(aux!=NULL && !equal(aux->data,data)) {
        aux=aux->next;
        count++;
    }
    
    return (aux==NULL)?-1:count;
}

Node* getNodeByPos(LinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;

    Node *aux = list->first;

    for (int count=0;(aux!=NULL && count<pos);count++,aux=aux->next);
    return aux;
}

void* getPos(LinkedList *list, int pos) {
    Node *aux = getNodeByPos(list,pos);
    if (aux==NULL) 
        return NULL;
    else
        return aux->data;
}

int add(LinkedList *list, int pos, void *data) {
    if (pos <= 0) return push(list,data);

    Node *aux = getNodeByPos(list, (pos-1));
    if (aux==NULL) return -2;
    
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode==NULL) return -1;
    
    newNode->data = data;
    newNode->next = NULL;
    
    newNode->next = aux->next;
    aux->next = newNode;
    
    list->size++;
    
    return 1;
}

int addAll(LinkedList *listDest, int pos, LinkedList *listSource) {
    if (listDest==NULL || isEmpty(listDest)) return -1;
    if (listSource==NULL || isEmpty(listSource)) return -2;

    Node *last = NULL;
    for (last = listSource->first;last->next!=NULL;last=last->next);
    if (pos == 0) {
        last->next = listDest->first;
        listDest->first = listSource->first;
    } else {
        Node *aux = getNodeByPos(listDest, (pos-1));
        if (aux==NULL) return -3;        
        last->next = aux->next; 
        aux->next = listSource->first;
    }
    listDest->size+=listSource->size;
    return listSource->size;
}

void* removePos(LinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;
    
    Node *nodeRemove = NULL;
    Node *aux = NULL;
       
    if (pos<=0)
        return dequeue(list);
    else
        aux = getNodeByPos(list, pos-1);

    nodeRemove = aux->next;
    aux->next = nodeRemove->next;
    
    void* dataRemove = nodeRemove->data;
    free(nodeRemove);
    list->size--;
    
    return dataRemove;
}

bool removeData(LinkedList *list, void *data, compare equal) {
    if (isEmpty(list)) return -1;

    Node *nodeRemove = NULL;
    if (equal(list->first->data,data)) {
        nodeRemove = list->first;
        list->first = list->first->next;
        free(nodeRemove->data);
        free(nodeRemove);
        list->size--;
        return true;
    } else {
        Node *aux = list->first;
        while(aux->next!=NULL && !equal(aux->next->data,data))
            aux=aux->next;
    
        if (aux->next!=NULL) {
            Node *nodeRemove = aux->next;
            aux->next = nodeRemove->next;
            free(nodeRemove->data);
            free(nodeRemove);
            list->size--;
            return true;
        } else {
            return false;
        }
    }
}