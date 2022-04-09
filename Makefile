all: clear pointers list dlist hash traberiseufelipe

pointers:
	@echo -e "\nCompilando ponteiros"
	gcc pointers.c -o pointers
	gcc pointers2.c -o pointers2
	@echo -e "\nHabilitando execução"
	chmod +x pointers
	chmod +x pointers2

list:
	@echo -e "\nCompilando Listas Dinâmicas"
	gcc LinkedList.h LinkedList.c LinkedListTest.c -o linkedlist
	@echo -e "\nHabilitando execução"
	chmod +x linkedlist

dlist:
	@echo -e "\nCompilando Listas Duplas Dinâmicas"
	gcc DoublyLinkedList.h DoublyLinkedList.c DoublyLinkedListTest.c -o doublylinkedlist
	@echo -e "\nHabilitando execução"
	chmod +x doublylinkedlist

hash:
	@echo -e "\nCompilando Hash"
	gcc log.h log.c DoublyLinkedList.h DoublyLinkedList.c Hash.h Hash.c HashTest.c -std=c99 -o hash
	@echo -e "\nHabilitando execução"
	chmod +x hash
	
traberiseufelipe:
	@echo -e "\nCompilando Trabalho do Eriseu e do Felipe"
	gcc log.h log.c DoublyLinkedList.h DoublyLinkedList.c Hash.h Hash.c HashPalavras.c -std=c99 -o traberiseufelipe
	@echo -e "\nHabilitando execução"
	chmod +x traberiseufelipe	

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers pointers2 linkedlist doublylinkedlist hash traberiseufelipe