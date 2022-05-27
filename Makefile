all: clear pointers list dlist hash blockchain

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

blockchain:
	@echo -e "\nCompilando Blockchain"
	gcc log.h log.c sha-256.h sha-256.c Blockchain.h Blockchain.c BlockchainTest.c -std=c99 -o blockchain
	@echo -e "\nHabilitando execução"
	chmod +x blockchain
	
geralList:
	@echo -e "\nCompilando Geral List"
	gcc log.h log.c GLinkList.c GLinkList.h GLinkListTest.c -std=c99 -o geralList
	@echo -e "\nHabilitando execução"
	chmod +x geralList
	
BST:
	@echo -e "\nCompilando By List"
	gcc log.h log.c BinarySearchTree.c BinarySearchTree.h BinarySearchTreeTest.c -std=c99 -o BST
	@echo -e "\nHabilitando execução"
	chmod +x BST

	
CT:
	@echo -e "\nCompilando By List"
	gcc log.h log.c CompressionTree.c -std=c99 -o CT
	@echo -e "\nHabilitando execução"
	chmod +x CT

AB:
	@echo -e "\nCompilando By List"
	gcc log.h log.c arvoreB.c -std=c99 -o AB
	@echo -e "\nHabilitando execução"
	chmod +x AB

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers pointers2 linkedlist doublylinkedlist hash blockchain geralList BST CT AB
