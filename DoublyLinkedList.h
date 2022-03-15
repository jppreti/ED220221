#ifndef DataStructure_DoublyLinkedList_h
#define DataStructure_DoublyLinkedList_h

enum boolean {
    true = 1, false = 0
};


typedef enum boolean bool;

typedef struct Node {
    void *data;
    struct Node *next, *prev;
}Node;

typedef struct DoublyLinkedList {
    Node *first;
    int size;
}DoublyLinkedList;

typedef bool (*compare)(void*,void*);

void init(DoublyLinkedList *list);
int enqueue(DoublyLinkedList *list, void *data);
void* dequeue(DoublyLinkedList *list);
void* first(DoublyLinkedList *list);
void* last(DoublyLinkedList *list);
int push(DoublyLinkedList *list, void *data);
void* pop(DoublyLinkedList *list);
void* top(DoublyLinkedList *list);
bool isEmpty(DoublyLinkedList *list);
int indexOf(DoublyLinkedList *list, void *data, compare equal);
void* getPos(DoublyLinkedList *list, int pos);
Node* getNodeByPos(DoublyLinkedList *list, int pos);
int add(DoublyLinkedList *list, int pos, void *data);
int addAll(DoublyLinkedList *listDest, int pos, DoublyLinkedList *listSource);
void* removePos(DoublyLinkedList *list, int pos);
bool removeData(DoublyLinkedList *list, void *data, compare equal);

#endif