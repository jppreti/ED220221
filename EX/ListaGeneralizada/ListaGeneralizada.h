#ifndef LISTA_GENERALIZADA_H
#define LISTA_GENERALIZADA_H

#include <stdlib.h>
#include <stdio.h>

enum elem_t {type_int, type_sublist};


union list_info {
    int atom;
    struct Node* sublist;
};

typedef struct Node{
    enum elem_t type;
    union list_info info;
    struct Node* next;
}Node;

void show(Node**);

/* Node* atom(int i){
    Node* n = (Node*)malloc(sizeof(Node));
    n->info.i = i;
    n->type = type_int;
    return n;
} */

int addAtom(Node** l, int atom){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) return -1;
    newNode->type = type_int;
    newNode->info.atom = atom;
    newNode->next = NULL;

    if(*l == NULL) *l = newNode;
    else{
        Node* aux = *l;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = newNode;
    }
    return 1;
}

/* Node* subList(Node* sublist){
    Node* n = (Node*)malloc(sizeof(Node));
    n->info.sublist = sublist;
    n->type = type_sublist;
    return n;
} */

int addList(Node** l, Node** subL){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) return -1;
    newNode->type = type_sublist;
    newNode->info.sublist = *subL;
    newNode->next = NULL;

    if(*l == NULL) *l = newNode;
    else{
        Node* aux = *l;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = newNode;
    }
    return 1;
}

/* Node *concat(Node* ap_elem, Node* ap_list){
    ap_elem->next = ap_list;
    return ap_elem;
} */

Node* head(Node** l){
    Node* aux = *l;
    printf("(");
    if(aux->type == type_int){
        printf("%d", aux->info.atom);
    }else{
        show(&aux->info.sublist);
    }
    printf(")");
}

Node* tail(Node** l){
    Node* aux = *l;
    printf("(");
    while(aux->next !=NULL){
        if(aux->next->type == type_int) {
            printf("%d", aux->next->info.atom);
        }else{
            tail(&aux->next->info.sublist);
        }
        if(aux->next == NULL){
            break;
        }else{
            printf(",");
            aux = aux->next;
        }
    }
    printf(")");
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

void show(Node** l){
    Node* aux = *l;
    printf("(");
    while (aux != NULL){
        if (aux->type == type_int){
        	printf("%d", aux->info.atom); 
		}else {
			show(&aux->info.sublist);
		}
    	if(aux->next == NULL){
			break;
		} else {
			printf(",");
			aux = aux->next;
		}     
    }
    printf(")");
}

#endif // !LISTA_GENERALIZADA_H