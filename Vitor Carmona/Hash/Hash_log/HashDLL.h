#ifndef DataStructure_DoublyLinkedList_h
#define DataStructure_DoublyLinkedList_h

#include <stdbool.h>

/* enum boolean {
    true = 1, false = 0
};

typedef enum boolean bool; */

typedef struct Node {
    void *data;
    struct Node *previous;
    struct Node *next;
}Node;

typedef struct DoublyLinkedList {
    Node *first;
    int size;
}DoublyLinkedList;

typedef bool (*compare)(void*,void*);
typedef void (*printNode)(void*);

void init(DoublyLinkedList *list) {
    Node *trashNode = (Node*)malloc(sizeof(Node));
    trashNode->data=NULL;
    trashNode->previous=trashNode;
    trashNode->next=trashNode;
    list->first=trashNode;
    list->size=0;
}

int enqueue(DoublyLinkedList *list, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode==NULL) return -1;

    newNode->data = data;
    newNode->next = list->first;
    newNode->previous = list->first->previous;

    list->first->previous->next = newNode;
    list->first->previous = newNode;
    
    list->size++;
    return 1;
}

void* dequeue(DoublyLinkedList *list);
void* first(DoublyLinkedList *list);
void* last(DoublyLinkedList *list);
int push(DoublyLinkedList *list, void *data);
void* pop(DoublyLinkedList *list);
void* top(DoublyLinkedList *list);

bool isEmpty(DoublyLinkedList *list) {
    return (list->size==0);
}

int indexOf(DoublyLinkedList *list,void *data,compare equal) {
    if (isEmpty(list)) return -1;
    int count=0;
    Node *aux = list->first->next;
    
    while(aux!=list->first && !equal(aux->data,data)) {
        aux=aux->next;
        count++;
    }
    
    return (aux==list->first)?-1:count;
}

Node* getNodeByPos(DoublyLinkedList *list,int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;
    Node *aux = list->first->next;
    for (int count=0;(aux!=list->first && count<pos);count++,aux=aux->next);
    return aux;
}

void* getPos(DoublyLinkedList *list,int pos);
int add(DoublyLinkedList *list, int pos, void *data);
int addAll(DoublyLinkedList *listDest, int pos, DoublyLinkedList *listSource);

void* removePos(DoublyLinkedList *list, int pos) {
    if (isEmpty(list) || pos>=list->size) return NULL;
    
    Node *nodeRemove = getNodeByPos(list, pos);
    
    nodeRemove->previous->next = nodeRemove->next;
    nodeRemove->next->previous = nodeRemove->previous;
    
    void* dataRemove = nodeRemove->data;
    free(nodeRemove);
    list->size--;
    
    return dataRemove;
}

bool removeData(DoublyLinkedList *list, void *data, compare equal);

void show(DoublyLinkedList *list, printNode print) {
    Node *aux = list->first->next;
    while (aux!=list->first) {
        print(aux->data);
        aux=aux->next;
    }
    printf("\n");
}

void showMem(DoublyLinkedList *list);

#endif