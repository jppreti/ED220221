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

typedef struct LinkedList {
    Node *first;
    Node *last;
    int size;
}LinkedList;

typedef bool (*compare)(void*,void*);

void init(LinkedList *list);
int enqueue(LinkedList *list, void *data);
void* dequeue(LinkedList *list);
void* first(LinkedList *list);
void* last(LinkedList *list);
int push(LinkedList *list, void *data);
void* pop(LinkedList *list);
void* top(LinkedList *list);
bool isEmpty(LinkedList *list);
int indexOf(LinkedList *list, void *data, compare equal);
void* getPos(LinkedList *list, int pos);
Node* getNodeByPos(LinkedList *list, int pos);
int add(LinkedList *list, int pos, void *data);
int addAll(LinkedList *listDest, int pos, LinkedList *listSource);
void* removePos(LinkedList *list, int pos);
bool removeData(LinkedList *list, void *data, compare equal);

#endif