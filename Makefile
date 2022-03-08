all: clear pointers list

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

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers pointers2 linkedlist
