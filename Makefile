all: clear pointers list dlist hash blockchain traberiseufelipe glist ctree

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
	
glist:
	@echo -e "\nCompilando Listas Generalizadas"
	gcc log.h log.c GeneralizedLinkedList.h GeneralizedLinkedList.c -std=c99 -o glist
	@echo -e "\nHabilitando execução"
	chmod +x glist	

ctree:
	@echo -e "\nCompilando Compressão em Árvore"
	gcc log.h log.c CompressaoArvore.h CompressaoArvore.c -std=c99 -o ctree
	@echo -e "\nHabilitando execução"
	chmod +x ctree

hash:
	@echo -e "\nCompilando Hash"
	gcc log.h log.c DoublyLinkedList.h DoublyLinkedList.c Hash.h Hash.c HashTest.c -std=c99 -o hash
	@echo -e "\nHabilitando execução"
	chmod +x hash
	
trabef:
	@echo -e "\nCompilando Trabalho do Eriseu e do Felipe"
	gcc log.h log.c DoublyLinkedList.h DoublyLinkedList.c Hash.h Hash.c HashPalavras.c -std=c99 -o traberiseufelipe
	@echo -e "\nHabilitando execução"
	chmod +x traberiseufelipe	

blockchain:
	@echo -e "\nCompilando Blockchain"
	gcc log.h log.c sha-256.h sha-256.c Blockchain.h pointers.c Blockchain.c BlockchainTest.c -std=c99 -o blockchain
	@echo -e "\nHabilitando execução"
	chmod +x blockchain

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers pointers2 linkedlist doublylinkedlist hash blockchain glist traberiseufelipe ctree