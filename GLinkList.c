#include "GLinkList.h"
#include <stdin.h>

int addAtom(Node *list, int put){
	Node *navg = list;
	while(1){
		if(navg.next == list){
			navg.atom = put;
			return 1;
		} 
	}
}
int addList(Node **list, Node **subList){
	
}
Node* head(Node *list){
	
}
Node* tail(Node *list){
	
}
void show(Node *list){
	
}
boolean search(Node *list, int atom){
	
}
int depth(Node *list){
	
}